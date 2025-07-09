# CMakeProject
Template repository for cmake project
Fork me and replase RENAME_ME to Name of your new project.

1. Clone this repository 
2. Run ./init.sh NewProjectName 

# This template supports next build targets:

|   Command or make target   |  Description    |
|------|------|
| **make test** | The run tests for a project (dependet of Qt Tests, so you need to add Qt in Cmake using CMAKE_PREFIX_PATH) |
| **make doc** | The generate a documentation for a project (dependet of doxygen) |
| **make deploy** | The generate distribution for a project (dependet of CQtDeployer) |
| **make release** | The prepare Qt Installer framework repository for a project, generate a snap package and APK file for android (dependet of CQtDeployer,  snapcraft, AndroidDeployer). |
