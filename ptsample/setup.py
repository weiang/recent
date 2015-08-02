#!/usr/bin/env python
# -*- encoding=utf-8 -*-

from distutils.core import setup, Extension

setup(name="pt", ext_modules=[
    Extension('pt',
        ['ptsample.c'],
        include_dirs = ['../sample', '..'],
        )
    ]
)
