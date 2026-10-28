#!/bin/bash

# Source the TEST_DIRS variable from realworld18dirs.sh
if [ ! -f ./realworld18dirs.sh ]; then
    echo "Error: File './realworld18dirs.sh' does not exist."
    exit 1
fi

source ./realworld18dirs.sh

# Check if TEST_DIRS is defined
if [ -z "${TEST_DIRS}" ]; then
    echo "Error: TEST_DIRS is not defined in './realworld18dirs.sh'."
    exit 1
fi

# Iterate over each directory in TEST_DIRS
for name in ${TEST_DIRS}; do
  # Check if the directory exists
  if [ ! -d "$name" ]; then
      echo "Warning: Directory '$name' does not exist. Skipping..."
      continue
  fi

  echo "Cleaning directory: $name"

  # Navigate to the directory
  cd "$name" || { echo "Error: Could not enter directory '$name'. Skipping..."; continue; }

  # Remove specified files and directories
  rm -rf ./_mt_main_result
  rm -f ./_LA__mt_main.c
  rm -f ./istLab__mt_main.c
  rm -f ./label_istLab__mt_main.c
  rm -f ./_mt_main.c
  rm -f ./seq_istLab__mt_main.c
  rm -f ./slice_seq_istLab__mt_main.c
  rm -f ./slice_tmp_seq_istLab__mt_main.c
  rm -f ./_cs__mt_main.c
  rm -f ./_mt_main.swarm.tar
  rm -f ./reducedConfig.json
  rm -f ./schedulingSeqConfig.json
  rm -f ./SSR__mt_main.c
  rm -f ./SSR_Runtime.json
  rm -f ./violation.info
  rm -f ./_mt_main_auto_config.json
  rm -f ./output.log

  # Return to the parent directory
  cd ..

done

echo "Cleanup completed successfully."