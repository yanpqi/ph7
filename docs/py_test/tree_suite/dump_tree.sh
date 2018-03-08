#/bin/bash
OLD_TREE_PATH=$TREE_PATH
OLD_SCRIPT_PATH=$SCRIPT_PATH

TREE_PATH=/tmp/tri_trees
SCRIPT_PATH=$(cd `dirname $0`; pwd)
mkdir $TREE_PATH && rm $TREE_PATH/*.txt
adb pull /sdcard/domTree.txt $TREE_PATH/
adb pull /sdcard/renderTree.txt $TREE_PATH/
adb pull /sdcard/paintTree.txt $TREE_PATH/
python $SCRIPT_PATH/to_utf8.py $TREE_PATH/domTree.txt
python $SCRIPT_PATH/to_utf8.py $TREE_PATH/renderTree.txt
python $SCRIPT_PATH/to_utf8.py $TREE_PATH/paintTree.txt

TREE_PATH=$OLD_TREE_PATH
SCRIPT_PATH=$OLD_SCRIPT_PATH
