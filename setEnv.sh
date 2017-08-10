#!/bin/bash

export ConnectedVision=$(dirname $(readlink -f "$0"))

echo ""
echo "make sure to execute this script by calling \"source ./setEnv.sh\" or \". ./setEnv.sh\" in order to run it in the current shell"
echo ""

echo "setting environment variable \"ConnectedVision\" (only for the current shell) to:"
echo "${ConnectedVision}"
echo ""