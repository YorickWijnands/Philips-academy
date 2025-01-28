FROM ghcr.io/philips-software/amp-devcontainer:latest

# Install any additional packages you need
RUN apt-get update && apt-get install -y \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /workspace

# Copy the project files into the container
COPY . .

# Set the default command to run when starting the container
CMD ["bash"]