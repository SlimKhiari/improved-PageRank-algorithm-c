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

Here is another run result with another graph with a few more hub and authoritative nodes with a dumping factor of 0.85:

![Screenshot from 2023-01-26 08-31-22](https://user-images.githubusercontent.com/73532355/214781487-d6fb14d2-ae1c-44a9-b18e-649259c16001.png)

![Screenshot from 2023-01-23 13-10-25](https://user-images.githubusercontent.com/73532355/214781515-aecd9a22-3034-4b95-96bb-02af58cd12d0.png)

![Screenshot from 2023-01-23 13-07-59](https://user-images.githubusercontent.com/73532355/214781313-cc95d4c6-a075-45e9-8b6f-0e41f66144c7.png)

By changing the dumping factor to 0.95, we see that the order of importance remains the same but with higher values for the first pages and lower values for the last pages:

![Screenshot from 2023-01-26 08-44-53](https://user-images.githubusercontent.com/73532355/214782759-050ef658-5369-4ce6-a00b-86ae927d92ae.png)





