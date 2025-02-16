# `ls_new` - Extended version of the `ls` command"

## Features ✨

*   Display hidden files (`-a`)
*   Detailed file information (`-l`)
*   Recursive traversal with and without threads  (`-r`, `-R`)
*   Recursive listing of subdirectories with parallel processing (threads) (`-z`)
*   Sorting by size, time, or alphabetically (`-S`, `-t`, `-X`)
*   Filtering by file pattern (`"*.(pattern)"`)

## Installation 🛠️

1.  **Install prerequisites**

    ```bash
    sudo apt update && sudo apt install cmake make gcc
    ```

2.  **Clone the repository**

    ```bash
    git clone https://<TOKEN>@github.com/PhoenixMaster123/ls_new.git
    cd ls_new
    ```

3.  **Create a build directory**

    ```bash
    mkdir build
    cd build
    ```

4.  **Configure CMake**

    ```bash
    cmake ..
    ```

5.  **Compile the program**

    ```bash
    make
    ```

6.  **Run the program**

    ```bash
    ./ls_new [Optionen] [Pfad]
    ```

## Available Options ⚙️

| Option | Beschreibung |
|---|---|
| `-a` | Shows all files, including hidden ones (files starting with `.`) |
| `-l` | Displays detailed information such as permissions, size, and date. |
| `-r` | Recursively traverses directories (without threads) |
| `-R` | Recursively traverses directories with parallel processing (threads) |
| `-z` | Recursively lists subdirectories with parallel processing (threads) |
| `-t` | Sorts by timestamp (newest first) |
| `-S` | Sorts by file size (largest first) |
| `-X` | Sorts by file extension |
| `"*.(pattern)"` | Filters files based on the specified pattern |

## Practical Examples 💡

1.  **List files in the current directory**

    ```bash
    ./ls_new
    ```

2.  **Show all files (including hidden ones)**

    ```bash
    ./ls_new -a
    ```

3.  **Display detailed file information**

    ```bash
    ./ls_new -l
    ```

4.  **Recursive listing of a directory without threads**

    ```bash
    ./ls_new -r /path/to/directory
    ```

5.  **Recursive listing of a directory with threads**

    ```bash
    ./ls_new -R /path/to/directory
    ```

6.  **Sort by size**

    ```bash
    ./ls_new -S
    ```

7.  **Sort output by timestamp, newest first**

    ```bash
    ./ls_new -t
    ```

8. **Recursively list subdirectories using threads**
    ```bash
    ./ls_new -z
    ```

9.  **Sort files by extension**

    ```bash
    ./ls_new -X
    ```

10.  **Show only specific files (e.g., all PNG files)**
     ```bash
     ./ls_new "*.png"
     ```
## ls_new: Explained - An Advanced Version of the ls Command (5 min.) (German)
https://github.com/user-attachments/assets/1cd3e182-46cb-4bb7-a818-f3e654dda45b

Video link: [ls_new](https://github.com/user-attachments/assets/1cd3e182-46cb-4bb7-a818-f3e654dda45b)

## License ⚖️

This project is licensed under the MIT License. More details can be found in the [LICENSE](LICENSE) file.

## Authors 👨‍💻👩‍💻

*   Enrico Ebert
*   Max Tremel
*   Kristian Popov
*   Zacharias Priller
