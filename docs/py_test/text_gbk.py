#!/usr/bin/env python
#coding:gbk

# '哈哈'stored in gbk, it's right, but in utf8, when runs, it's read as gbk for lang declared.
# error may occur sometimes for other chinese characters.

# in vim, first input :set fenc=gbk, then :w, run the script, see output.
# in vim first input :set fenc=utf8, then :w, run the script, see output.

ss = u'哈哈'

print repr(ss)
print 'ss:%s' % ss
