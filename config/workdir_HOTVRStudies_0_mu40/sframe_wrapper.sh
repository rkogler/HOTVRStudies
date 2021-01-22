#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH_STORED:$LD_LIBRARY_PATH
export PATH=$PATH_STORED:$PATH
sframe_main $1
        