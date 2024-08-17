## Instructions to Compile the Code

1. **Open Terminal or Command Prompt**:
   - On **Mac** or **Linux**, open the Terminal application.
   - On **Windows**, open Command Prompt or PowerShell.

2. **Navigate to the Project Directory**:
   - Use the `cd` command to navigate to the directory where your `main.c++` file is located. For example:
     ```sh
     cd /path/to/your/project
     ```

3. **Compile the Code**:
   - Use the `g++` compiler to compile the code with the C++14 standard. Run the following command:
     ```sh
     g++ -std=c++14 -o main.out main.c++
     ```

### Notes:
- Ensure that you have `g++` installed on your system.
  - **Mac**: You can install it using Homebrew if it's not already installed:
    ```sh
    brew install gcc
    ```
  - **Linux**: You can install it using your package manager. For example, on Debian-based systems:
    ```sh
    sudo apt-get install g++
    ```
