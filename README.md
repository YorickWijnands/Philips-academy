# Philips-academy

## Setup Instructions

### Prerequisites

1. **Install Visual Studio Code**: Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. **Install WSL and Ubuntu**:
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

1. **Select Target**: After the dev container is set up, select the target `stm32f429zi`.
2. **Build the Project**: Use the build command in Visual Studio Code to build the project.

## Adding a New Project

To add a new project under [src](http://_vscodecontentref_/1), follow these steps:

1. **Create a New Directory**: Create a new directory under [src](http://_vscodecontentref_/2) for your project.
    ```sh
    mkdir src/<new_project>
    ```

2. **Add Source Files**: Add your source files (`.cpp` and `.hpp`) to the new directory.

3. **Create CMakeLists.txt**: Create a [CMakeLists.txt](http://_vscodecontentref_/3) file in the new directory with the following content:
    ```cmake
    # filepath: /workspaces/Philips-academy/src/<new_project>/CMakeLists.txt

    # Automatically add all .cpp files in the current directory
    file(GLOB SOURCES "*.cpp")

    # Add the source files to the executable
    add_executable(${PROJECT_NAME} ${SOURCES})

    emil_build_for(${PROJECT_NAME} TARGET_MCU_VENDOR st PREREQUISITE_BOOL HALST_BUILD_EXAMPLES)

    target_compile_definitions(${PROJECT_NAME} PUBLIC
        NUCLEO=Nucleo144Ui
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        services.util
        hal_st.instantiations
    )

    halst_target_default_linker_scripts(${PROJECT_NAME})
    halst_target_default_init(${PROJECT_NAME})

    emil_generate_artifacts(TARGET ${PROJECT_NAME} LST MAP BIN HEX)
    ```
