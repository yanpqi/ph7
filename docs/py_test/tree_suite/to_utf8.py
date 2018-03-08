#!/usr/bin/env python
import sys
import re
import os

def replace_to_u(matched):
    if len(matched.group(1)) >= 4:
        return r'\u' + matched.group(1)
    new_text = r'0000' + matched.group(1)
    return r'\u' + new_text[-4:]

# Sometimes we will have \uA9 {aka '@'}, when decode error, we need to convert to
# \u00A9.
def decode_string(content):
    content = re.sub(r'\\x{([0-9a-fA-F]+)}', replace_to_u, content)
    while True:
        try:
            content = content.decode("unicode-escape")
            break
        except UnicodeDecodeError, e:
            new_content = content[:e.start + 2]  + '00' + content[e.start + 2:]
            content = new_content
            continue
    return content

if __name__ == '__main__':
    if not os.path.isfile(sys.argv[1]):
        print decode_string(sys.argv[1])
        sys.exit(0)

    new_content = u''
    new_file = sys.argv[1] + '.utf8'
    with open(sys.argv[1], 'r') as f:
        content = f.read()
        # \x{XXXX} should be replaced to XXXX, be care \x should match with \\x even in raw string.
        new_content = decode_string(content)

    with open(new_file, 'w') as f:
        try:
            f.write(new_content.encode('utf8'))
        except IOError:
            print 'Failed to write to file %s' %(new_file)

