#
# This macro is defined by the developer.  It is a list of all subdirectories
# that build required components.  Each subdirectory should be on a separate
# line using the line continuation character.  This will minimize merge
# conflicts if two developers adding source files to the same component.
# The order of the directories is the order that they will be built when
# doing a build.
#

DIRS=dir1   \
     dir2   \
     dir3   \
     dir4

#
# This macro is defined by the developer.  It is a list of all subdirectories
# that build optional components.  Each subdirectory should be on a separate
# line using the line continuation character.  This will minimize merge
# conflicts if two developers adding source files to the same component.
# The order of the directories is the order that they will be built when
# doing a build.
#

OPTIONAL_DIRS=dir8  \
              dir9
