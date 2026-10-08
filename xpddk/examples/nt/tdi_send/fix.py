import os
import sys
import pefile

if len(sys.argv) != 2:
    print('Usage: {} xxx'.format(sys.argv[0]))
    sys.exit()

fname = sys.argv[1]
pe = pefile.PE(fname);
pe.OPTIONAL_HEADER.CheckSum = pe.generate_checksum();
pe.write(fname);
