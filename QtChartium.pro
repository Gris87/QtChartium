TEMPLATE = subdirs

SUBDIRS = \
  lib \
  examples

# where to find the sub projects - give the folders
lib.subdir      = libs/qtchartium
examples.subdir = examples

# what subproject depends on others
examples.depends = lib
