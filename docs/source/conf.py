#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import subprocess

on_rtd = os.environ.get('READTHEDOCS', None) == 'True'

if on_rtd:
    subprocess.call('cd ..; doxygen', shell=True)

import sys
import os
import sphinx_rtd_theme



if True:
    subprocess.call('cd ../.. && cmake .',          shell=True)
    subprocess.call('cd ../.. && make -j .',        shell=True)
    #subprocess.call('cd ../.. && make install .',   shell=True)

sys.path.append(os.path.abspath('../../python'))


import cpptools



html_theme = "sphinx_rtd_theme"
#html_theme = "classic"
html_theme_path = [
    sphinx_rtd_theme.get_html_theme_path(),
    'mytheme',
    '.'
]


# html_theme_options = {
#   "codebgcolor": 'black'
# }


#html_static_path = ['_static']

extensions = ['breathe']
breathe_projects = { 'cpptools': '../xml' }
templates_path = ['_template']
source_suffix = '.rst'
master_doc = 'index'
project = 'cpptools'
copyright = '2018, Thorsten Beier'
author = 'Thorsten Beier'


exclude_patterns = []
highlight_language = 'c++'
#pygments_style = 'sphinx'
todo_include_todos = False
htmlhelp_basename = 'cpptools_doc'

pygments_style = 'monokai'