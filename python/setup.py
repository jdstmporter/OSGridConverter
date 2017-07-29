'''
Created on 27 Jul 2017

@author: julianporter
'''
"""A setuptools based setup module.
See:
https://packaging.python.org/en/latest/distributing.html
https://github.com/pypa/sampleproject
"""

from setuptools import setup, find_packages
from codecs import open
from os import path

here = path.abspath(path.dirname(__file__))

with open(path.join(here, 'README.rst'), encoding='utf-8') as f:
    long_description = f.read()

setup(
    name='OSGridConverter',
    version='0.1.2',
    description='Library to convert co-ordinates between the (UK) Ordnance Survey National Grid and latitude/longitude',
    long_description=long_description,
    url='https://github.com/....',

    author='Julian Porter',
    author_email='julian@jpembedded.solutions',
    license='MIT',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Intended Audience :: Science/Research',
        'Intended Audience :: Other Audience',
        'Topic :: Education',
        'Topic :: Internet :: WWW/HTTP :: WSGI :: Application',
        'Topic :: Scientific/Engineering :: GIS',
        'Topic :: Scientific/Engineering :: Visualization',
        'Topic :: Software Development :: Libraries',
        'Topic :: Utilities',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Operating System :: MacOS',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: POSIX :: Linux'
    ],

    # What does your project relate to?
    keywords='gis mapping coordinates grid-reference mapping ordiance-survey lat-long',

    packages=find_packages(),
    install_requires=[],
    python_requires='>=3.4',
    
    extras_require={},
    package_data={},
    data_files=[],
    entry_points={},
    test_suite='test',
    tests_require=['OSGridConverter']
)
