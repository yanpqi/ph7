#!/usr/bin/env python

import sys
import subprocess
import re

class LogcatExtension(object):
    def __init__(self, adb_args=None, allows=None, denys=None):
        self._allows = allows
        self._denys = denys
        self.adb_args = adb_args

    def _generate_adb_cmd(self):
        return 'adb logcat'

    def _filte(self, content):
        if not self._allows or content.find(self._allows) > 0:
            return True
        return False

    @staticmethod
    def _convert_ustr(content):
        pattern = re.compile(r'\\x\{([0-9a-fA-F]+)\}')
        content = re.sub(pattern, '\u\\1', content)
        try:
            content = content.decode("unicode-escape").encode("utf-8")
        except:
            content = content.decode('utf8')
        return content

    def start(self):
        command = self._generate_adb_cmd()
        proc_adb = subprocess.Popen(
                command,
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE)
        for line in proc_adb.stdout:
            if not self._filte(line):
                continue
            print self._convert_ustr(line)
        out, err = proc_adb.communicate()
        errcode = proc_adb.returncode

def main(argv=None):
    allows=argv[0] if len(argv) > 0 else None
    log = LogcatExtension(allows)
    log.start()

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
