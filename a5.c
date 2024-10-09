#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

//global variable
// struct Point* head;

typedef struct Point {
    int x;
    int y;
    struct Point *left;
    struct Point *right;
} Point; 

Point* createPoint(int x_val, int y_val) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->x = x_val;
    newPoint->y = y_val;
    newPoint->left = NULL;
    newPoint->right = NULL;
    return newPoint;
}

void addToTree(int x_val, int y_val, Point** head, int depth) {
    if ((*head) == NULL) 
    {
        (*head) = createPoint(x_val, y_val);
    }
    
    else //if "head" is already there
    {
        if (depth % 2 == 0) // even depth, performs x comparison
        {
            if (x_val <= (*head)->x) //add to left
            {
                // (*head)->left = newPoint;
                addToTree(x_val, y_val, &(*head)->left, depth + 1);
            }
            else if (x_val > (*head)->x)
            {
                addToTree(x_val, y_val, &(*head)->right, depth + 1);
            }
        }

        else if (depth % 2 != 0) // od depth, performs y comparison
        {
            if (y_val <= (*head)->y)
            {
                addToTree(x_val, y_val, &(*head)->left, depth + 1);
            }
            else if (y_val > (*head)->y)
            {
                addToTree(x_val, y_val, &(*head)->right, depth + 1);
            }

        }
    }
    return;
}

int pointsInCircle (int center_x, int center_y, int radius, Point* head) {
    if (head == NULL) 
    {
        return 0; // Check if head is NULL
    }

    int count = 0; //count of total points in circle
    
    //(point x - center x)^2 + (point y - center y)^2 = r^2
    //if the calculated r^2 is greater than the given r^2, then that point is not in circle, count does not change
    //if the calculated r^2 is less than or equal to the given r^2, then that point is in the circle, count += 1

    int rad_sq = ((head->x - center_x) * (head->x - center_x)) + ((head->y - center_y) * (head->y - center_y));

    if (rad_sq <= (radius * radius))
    {
        count++;
    }

    if ((head->x - center_x) * (head->x - center_x) <= (radius * radius) || (head->y - center_y) * (head->y - center_y) <= (radius * radius)) {
        count += pointsInCircle(center_x, center_y, radius, head->left);
        count += pointsInCircle(center_x, center_y, radius, head->right);
    } 
    else if (head->x > center_x) 
    {
        // Only check the left subtree
        count += pointsInCircle(center_x, center_y, radius, head->left);
    } 
    else 
    {
        // Only check the right subtree
        count += pointsInCircle(center_x, center_y, radius, head->right);
    }

    return count;
}

void freeTree(Point* head) {
    if (head == NULL) 
    {
        return;
    }
    freeTree(head->left);
    freeTree(head->right);
    free(head);
}

int main(int argc, char* argv[])
{    
    //check if filename is provided 
    if (argc < 2) {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return -1; // Exit if no filename is provided
    }

    //PART 1: BUILDING THE TREE
    //need to write code for file reading
    //need to split each line, left word is x, right word is y
    //make while loop to call build tree function for each node
    
    Point* head = NULL;
    char* filename = argv[1]; // The filename is now taken from command line argument
    // char filename[] = "input.txt"; //i just put input.txt for now

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return -1; //did not work
    }

    int x_val;
    int y_val;
    int depth = 0;

    while (fscanf(file, "%d %d", &x_val, &y_val) != EOF) 
    {
        addToTree(x_val, y_val, &head, depth); //starts at depth = 0 every time
    }

    fclose(file);
    //at this point tree has been built and file is closed

    //PART 2: GETTING CENTER AND RADIUS
    int center_x;
    int center_y;
    int radius;
    
    //printf("what center and what radius, for center put x and y \n");
    while (1)
    {
        scanf("%d %d %d", &center_x, &center_y, &radius);
        int count = pointsInCircle(center_x, center_y, radius, head);
        printf("%d\n", count);
    }

    freeTree(head);
    
    return 0;
    }