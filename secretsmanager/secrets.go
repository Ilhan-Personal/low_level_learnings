/*
 * Copyright (c) 2021 DevRev, Inc. All rights reserved.
 */

package secretsmanager

import (
	"context"
	"fmt"
	"sync/atomic"
	"time"

	"github.com/devrev/shared/log"
	"github.com/devrev/shared/secrets"
)

// FetchSecrets fetches secrets stored against the provided key from AWS
// secretsmanager. It is assumed that the values are stored in JSON format.
func FetchSecrets(key string) (map[string]string, error) {
	m, err := secrets.NewAWSSecretsManager()
	if err != nil {
		return nil, fmt.Errorf("failed to create secrets manager client: %v", err)
	}
	values := make(map[string]string)
	if err = m.FetchSecretsJSON(key, &values); err != nil {
		return nil, err
	}
	return values, nil
}

// fetchSecretsFunc is a variable holding the secrets fetching function, allowing
// for dependency injection during testing. By default, it points to FetchSecrets.
var fetchSecretsFunc = FetchSecrets

// FetchAndRefreshSecrets periodically fetches secrets from AWS Secrets Manager at the specified interval.
// It returns a function to access the latest secrets, and a cancel function
// that should be called to stop the refresh goroutine.
// The cancel function should always be called when you're done with the secrets to prevent memory leaks
// and ensure proper cleanup of background goroutines.
//
// Example:
//
//	getter, cancel, err := FetchAndRefreshSecrets("secret-key", 30*time.Second) // refresh every 30 seconds
//	if err != nil {
//		log.Fatal(err)
//	}
//	defer cancel() // ensure cancel is called when done
//
//	// secrets map will be automatically updated every 30 seconds
func FetchAndRefreshSecrets(key string, timeInterval time.Duration) (func() map[string]string, func(), error) {
	if timeInterval <= 0 {
		return nil, nil, fmt.Errorf("timeInterval must be greater than 0")
	}

	// Fetch initial secrets
	initialValues, err := fetchSecretsFunc(key)
	if err != nil {
		return nil, nil, fmt.Errorf("initial secrets fetch failed: %v", err)
	}

	// Create an atomic pointer to store the map safely
	var secretsPtr atomic.Pointer[map[string]string]

	// Store the initial values
	secretsPtr.Store(&initialValues)

	stop := make(chan struct{})

	go func() {
		ticker := time.NewTicker(timeInterval)
		defer ticker.Stop()

		for {
			select {
			case <-ticker.C:
				newValues, err := fetchSecretsFunc(key)
				if err != nil {
					log.Errorf(context.Background(), "failed to refresh secrets: %v\n", err)
					continue
				}

				// Store the new map atomically - this creates a new reference
				// that readers will start using without any locks
				secretsPtr.Store(&newValues)

			case <-stop:
				return
			}
		}
	}()

	// The getter function returns a copy of the current secrets map
	getter := func() map[string]string {
		// Load the current pointer to the map atomically
		currentPtr := secretsPtr.Load()
		if currentPtr == nil {
			return make(map[string]string)
		}

		// Make a copy of the map to return to callers
		// This ensures that even if the caller modifies the map,
		// it won't affect other readers
		result := make(map[string]string, len(*currentPtr))
		for k, v := range *currentPtr {
			result[k] = v
		}
		return result
	}

	cancel := func() {
		close(stop)
	}

	return getter, cancel, nil
}
