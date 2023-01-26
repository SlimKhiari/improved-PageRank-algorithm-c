# HPC

## PageRank algorithm

Here you will find the improved pageRank algorithm in c.

The "files_management.*" files are mainly intended for reading the file (in which we have the graph).

The "matrix_calculation.*" files are intended for calculations and processing related to the pageRank algorithm.

The "main.c" file is the implementation of the pageRank algorithm.

The "matrix.txt" file, representing the links between the nodes, must be in this form:

![Screenshot from 2023-01-23 13-10-25](https://user-images.githubusercontent.com/73532355/214036465-692daed0-654e-4e54-a366-61b45cead061.png)

the first line represents the number of nodes in the graph. Then, for each line, we have the links for each node (0 means no link).

## Launch of the program

![Screenshot from 2023-01-23 13-07-59](https://user-images.githubusercontent.com/73532355/214036097-f0dbf70a-9c07-44dc-9315-8083d09f2e7e.png)

## A few comments

By testing our code  with values 10^-6, 10⁻8 and 10⁻10 of TOLERANCE variable, the execution result remains the same.

Here is another run result with another graph with a few more hub and authoritative nodes:

file:///home/slim/Pictures/Screenshots/Screenshot%20from%202023-01-26%2008-31-22.png![image](https://user-images.githubusercontent.com/73532355/214781170-22af7259-95ce-4cd6-a9![Screenshot from 2023-01-23 13-10-25](https://user-images.githubusercontent.com/73532355/214781283-51bb202d-8181-4a4f-87a5-7e6f7c578d47.png)
1c-1e0eebb4505f.png)
![Uploading Screenshot from 2023-01-23 13-10-25.png…]()

![Screenshot from 2023-01-23 13-07-59](https://user-images.githubusercontent.com/73532355/214781313-cc95d4c6-a075-45e9-8b6f-0e41f66144c7.png)



