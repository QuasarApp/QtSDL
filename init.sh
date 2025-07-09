#!/bin/sh

echo "Project name: $1"

if [ $# -ne 1 ]
then
    echo "You call this script wtth wrong arguments."
    echo "Example for start script:"
    echo "./init.sh MyCmakeProject"
    echo "Usage: $0 <replacement_string>"

    exit 1
fi

replacement="$1"

rename_files_and_folders() {
    local dir="$1"
    local old_str="$2"
    local new_str="$3"

    for item in "$dir"/*; do
        if [ -d "$item" ]; then
            new_name=$(echo "$item" | sed "s/$old_str/$new_str/g")
            if [ "$item" != "$new_name" ]; then
                mv "$item" "$new_name"
                echo "Renamed directory: $item -> $new_name"
            fi
            rename_files_and_folders "$new_name" "$old_str" "$new_str"
        elif [ -f "$item" ]; then
            sed -i "s/$old_str/$new_str/g" "$item"

            new_name=$(echo "$item" | sed "s/$old_str/$new_str/g")
            if [ "$item" != "$new_name" ]; then
                mv "$item" "$new_name"
                echo "Renamed file: $item -> $new_name"
            fi
        fi
    done
}

uppercase_string=$(echo "$replacement" | tr '[:lower:]' '[:upper:]')

rename_files_and_folders "." "QTSDL_EXPORT" "${uppercase_string}_EXPORT"
rename_files_and_folders "." "QTSDL_VERSION" "${uppercase_string}_VERSION"
rename_files_and_folders "." "QTSDL_LIBRARY" "${uppercase_string}_LIBRARY"
rename_files_and_folders "." "QTSDL_EXAMPLE" "${uppercase_string}_EXAMPLE"
rename_files_and_folders "." "QTSDL_TESTS" "${uppercase_string}_TESTS"
rename_files_and_folders "." "QTSDL_PACKAGE_ID" "${uppercase_string}_PACKAGE_ID"

rename_files_and_folders "." "QtSDL" "$replacement"

echo "Replacement complete."


git config -f .gitmodules --get-regexp '^submodule\..*\.path$' |
    while read path_key path
    do
        url_key=$(echo $path_key | sed 's/\.path/.url/')
        url=$(git config -f .gitmodules --get "$url_key")
        git submodule add $url $path
    done
