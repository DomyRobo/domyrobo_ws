import os
from glob import glob
from setuptools import setup

package_name    = 'domyrobo_controller'
submodule       = 'domyrobo_controller/submodule'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name, submodule],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*_launch.py'))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='dhonan',
    maintainer_email='dhonan.hibatullah@gmail.com',
    description='Package for controlling Domyrobo motors via message publishing',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'domyrobo_controller_main = domyrobo_controller.domyrobo_controller_main:main',
            'domyrobo_teleop_main = domyrobo_controller.domyrobo_teleop_main:main',
        ],
    },
)
