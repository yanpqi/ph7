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

function run_server {
    cd $TOP_ROOT
    mkdocs serve -a 0.0.0.0:8000
}

alias to='to_dir '
alias run='run_server'
