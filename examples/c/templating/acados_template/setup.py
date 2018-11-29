from setuptools import setup, find_packages

import acados_template

setup(name='acados_template',
   version='0.1',
   description='a templating framework for acados',
   url='http://github.com/zanellia/acados',
   author='Andrea Zanelli',
   license='LGPL',
   packages = find_packages(),
   include_package_data = True,
   package_data={'': ['c_templates/template_example.in.c']},
   zip_safe=False)
