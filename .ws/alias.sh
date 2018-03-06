#!/bin/bash

function get_top {
   CURDIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd )
   TOP_ROOT=$(dirname "$CURDIR")
   echo $TOP_ROOT
}
get_top

function to_dir {
    if [ "x$1" == "x" ]; then
        cd $TOP_ROOT
    else
        cd $TOP_ROOT/docs/$1
    fi
}

alias to='to_dir '
