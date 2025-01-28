# Philips-academy

## Setup Instructions

### Prerequisites

1. **Install Visual Studio Code**: Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. **Install WSL and Ubuntu**:
    - Install Ubuntu from the Microsoft Store.
    - Open a terminal and run the following commands to enable WSL and Virtual Machine Platform:
      ```sh
      dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
      dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
      ```
    - Install WSL and Ubuntu:
      ```sh
      wsl --install
      ```
    - Open the Ubuntu WSL terminal and set it up.

### Clone the Project

1. **Fork the Project**: Fork the project repository to your own GitHub account.
2. **Clone the Forked Project**: Open the Ubuntu WSL terminal and clone your forked project:
    ```sh
    git clone <your-forked-repo-url>
    cd <your-forked-repo-directory>
    ```

3. **Initialize Submodules**: Run the following command to initialize and update submodules:
    ```sh
    git submodule update --init --recursive
    ```

### Setup Dev Container

1. **Install Dev Container Extension**: Open Visual Studio Code and install the "Remote - Containers" extension.
2. **Reload Visual Studio Code**: Use the command palette (`Ctrl+Shift+P`) and select `Developer: Reload Window`.
3. **Reopen in Container**: A popup should appear asking if you want to reopen the project in a container. Select "Reopen in Container".

### Build the Project

1. **Select Target**: After the dev container is set up, select the target `stm32f429zi` (or another microcontroller) for building the project for the microcontroller.
2. **Build the Project**: Use the build command in Visual Studio Code to build the project.

### Run Tests

1. **Select Configuration for Host Tooling and Tests**: Select the configuration for host tooling and tests to build and run tests on your local PC.
2. **Build the Tests**: Use the build command in Visual Studio Code to build the tests.
3. **Run the Tests**: Use the command palette (`Ctrl+Shift+P`) and select `CMake: Run CTest` to run the tests.

### Test Directory

The [tests](http://_vscodecontentref_/1) directory contains subdirectories for each project under [src](http://_vscodecontentref_/2). Each subdirectory includes test files and a [CMakeLists.txt](http://_vscodecontentref_/3) file to define the test build configuration. For example, the `tests/move_finger` directory contains tests for the `move_finger` project under [src](http://_vscodecontentref_/4).

To add a new test:

1. **Create a New Directory**: Create a new directory under [tests](http://_vscodecontentref_/5) for your project.
    ```sh
    mkdir tests/<new_project>
    ```

2. **Add Test Files**: Add your test files (`.cpp`) to the new directory.

3. **Create CMakeLists.txt**: Create a [CMakeLists.txt](http://_vscodecontentref_/6) file in the new directory with the following content:
    ```cmake
    # filepath: /workspaces/Philips-academy/tests/<new_project>/CMakeLists.txt

    # Get all test files
    file(GLOB TEST_SOURCES "*.cpp")

    # Add executable for tests
    add_executable(run<NewProject>Tests ${TEST_SOURCES})

    # Link Google Test libraries and the necessary project libraries
    target_link_libraries(run<NewProject>Tests gtest gtest_main services.util hal_st.instantiations)

    # Add test target
    gtest_discover_tests(run<NewProject>Tests)
    ```

By following these steps, you can build your main project for the STM32F429ZI microcontroller and run your tests on your local PC. The [CMakePresets.json](http://_vscodecontentref_/7) helps manage different build configurations, making it easy to switch between building for the microcontroller and running tests locally.