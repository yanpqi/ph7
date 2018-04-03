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
PID_FILE='/tmp/mkdocs_demon_lock.pid'
function run_server {
    if [ -f "$PID_FILE" ]; then
        echo 'A mkdocs has already running...'
        return
    fi
    cd $TOP_ROOT
    nohup mkdocs serve -a 0.0.0.0:8000 2>&1 & 
    echo $! > $PID_FILE
}

function kill_server {
     if [ -f "$PID_FILE" ]; then
        kill -9 `cat $PID_FILE`
        rm -f $PID_FILE
    fi  
}

alias to='to_dir '
alias run='run_server'
alias kl='kill_server'
