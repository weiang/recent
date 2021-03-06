
from distutils.core import setup, Extension 

setup(name='sample', 
            ext_modules=[
		Extension('sample',
			  ['pysample.c'],
			  include_dirs = ['..'],
			  define_macros = [('FOO', '1')],
			  undef_macros = ['BAR'],
			  library_dirs = ['..'],
			  libraries = ['sample', 'embed']
			  )
            ]
)


