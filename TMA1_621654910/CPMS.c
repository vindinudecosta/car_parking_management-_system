#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/* last no of my registration no is "0", therfore max slots of my cpms is 10+0 = 10;*/
#define PK_ARRAY_SIZE 10

/*manually initialize size of the pk_slot array “s” or “l” and  autmatically assign false to occupy*/
void slot_alloc(int i);
/*input vehicle details here.*/
void vehicle_detail(char v_no[10]);
/*input details to pk_slot array.*/
bool park_slot(int n);
/*Function to display pk_slot array details*/
void display(int j);
/*function to leave a vehicle from the system*/
void vehicle_leaving(char v_no[10]);
/*function to calculate the leaving time of the vehicle*/
void leave_timer(int e);

struct v_time
{
    int hour;
    int minute;
};

struct vehicle
{
    char car_no[10];
    char colour[10];
    char width[5];
    bool parked;
    struct v_time in_time;
    struct v_time out_time;
} vh1;

struct park
{
    char size[10];
    bool occupy;
    struct vehicle vh;
};

/*declaring a park slot array of defined size and intializing the array to zero.*/
struct park pk_slot[PK_ARRAY_SIZE] = {0};

int main()
{
    /*calling the slot allocation function to allocated the sizes of the slots manually.*/
    slot_alloc(PK_ARRAY_SIZE);

loop:
    for (int p = 0; p < 5; p++)
    { /* In this part of the code the program asks whether a vehicle in leaving the park or not */
        char response[5];
        char default_response[5] = {"e"};
        printf("IS A VEHICLE ENTERING(e) OR LEAVING(l) THE PARK(e/l): ");
        scanf("%s", response);
        printf("\n");

        /* If the operator enters entering response then the below code will ask for the registration
number and other vehicle details and will check for a available slot of same size in the parking slot  */
        if (strcmp(response, default_response) == 0)
        {
            char vehregister_no[10];
            printf("Enter vehicle register number (do not keep any spaces in between the characters): ");
            scanf("%s", vehregister_no);
            vehicle_detail(vehregister_no);
            printf("\n");
            printf("\n");
            printf("\n");

            for (int z = 0; z < PK_ARRAY_SIZE; z++)
            {
                bool flag = park_slot(z);
                if (flag == true)
                {
                    printf("VEHICLE CAN ENTER SLOT %d\n", z + 1);
                    printf("\n");
                    printf("\n");

                    break;
                }
                else if (flag == false && strcmp(vh1.width, pk_slot[z].size) != 0)
                {
                    printf("vehicle cannot enter slot %d\n,not a same size slot\n", z + 1);
                    printf("\n");
                    printf("\n");
                }
                else
                {
                    printf("vehicle cannot enter slot %d\n,occupied!\n", z + 1);
                    printf("\n");
                    printf("\n");
                }
            }
        }

        /* if the response is leaving, from this part of the code the program will ask to enter the registration no of the leaving vehicle
        and then will remove the vehicle from the cpms and print the vehicle information including the leaving time of the vehicle  */
        else
        {

            char vehleaving[10];
            printf("Enter registration number of the leaving vehicle (do not keep any spaces inbetween the characters) : ");
            scanf("%s", vehleaving);

            printf("\n");
            printf("\n");

            vehicle_leaving(vehleaving);
            printf("This vehicle is not inside the park!!!\n");
            printf("\n");
            printf("\n");
            printf("\n");
        }

        /* from this part of the code the program will ask whether the user wants to see the vehicle details inside the park slots ,
        if the reponse is "yes" then the program will display the vehicle details inside the park*/
        char select[5];
        char default_select[5] = {"y"};
        printf("WANT TO LOOK THE PARK ARRAY DETAILS (y/n)");
        scanf("%s", select);
        printf("\n");
        printf("\n");
        if (strcmp(select, default_select) == 0)
        {

            for (int q = 0; q < PK_ARRAY_SIZE; q++)
            {
                if (pk_slot[q].occupy == true)
                {
                    display(q);
                    printf("\n");
                }
                else
                {
                    printf("No vehicle inside slot %d\n", q + 1);
                    printf("\n");
                }
            }
        }
    }
    /* In this part of the code the program will ask the user whether to leave or exit  the CPMS */
    char leaveresponse[5];
    char defaultleavingresponse[5] = {"y"};

    printf("DO YOU WANT TO LEAVE THE CAR PARKING MANAGEMENT SYSTEM:(y/n)");
    scanf("%s", leaveresponse);

    if (strcmp(leaveresponse, defaultleavingresponse) == 0)
    {
        printf("good bye");
    }
    else
    {
        goto loop;
    }

    return 0;
}

/* manually initialize size of the pk_slot array “s” or “l” and  autmatically assign false to occupy*/

void slot_alloc(int i)
{

    for (int j = 0; j < i; j++)
    {

        printf("size of park slot %d(large[l] / small[s]):", j + 1);
        scanf("%s", &pk_slot[j].size);

        pk_slot[j].occupy = false;
    }

    printf("\n");
}

/* input vehicle details here.*/
void vehicle_detail(char v_no[10])
{

    char vehicle_colour[10];
    char vehicle_width[5];

    strcpy(vh1.car_no, v_no);

    printf("Enter the colour of the vehicle: ");
    scanf("%s", &vehicle_colour);
    strcpy(vh1.colour, vehicle_colour);

    printf("Width of the vehicle:");
    scanf("%s", &vehicle_width);
    strcpy(vh1.width, vehicle_width);

    printf("Enter in time (hour and minutes): ");
    scanf("%d %d", &vh1.in_time.hour, &vh1.in_time.minute);
}

/* input details to pk_slot array.*/

bool park_slot(int n)
{

    if (pk_slot[n].occupy == false)
    {
        int compare = strcmp(vh1.width, pk_slot[n].size);
        if (compare == 0)
        {

            pk_slot[n].occupy = true;

            pk_slot[n].vh = vh1;
            pk_slot[n].vh.parked = true;

            return true;
        }

        else
        {

            return false;
        }
    }

    else
    {

        return false;
    }
}
/*Function to display pk_slot array details*/
void display(int j)
{

    printf("Vehicle registration no : %s\n", pk_slot[j].vh.car_no);
    printf("Colour of the vehicle : %s\n", pk_slot[j].vh.colour);
    printf("Width of the vehicle (small[s]/large[l]) : %s\n", pk_slot[j].vh.width);
    if (pk_slot[j].vh.parked == true)
    {
        printf("Parked status: vehicle is parked\n");
    }

    printf("Entering time of the vehicle to the park : %d:%d\n", pk_slot[j].vh.in_time.hour, pk_slot[j].vh.in_time.minute);
    printf("leaving time of the vehicle from the park : %d:%d\n", pk_slot[j].vh.out_time.hour, pk_slot[j].vh.out_time.minute);
}
/*function to leave a vehicle from the system*/
void vehicle_leaving(char v_no[10])
{

    for (int p = 0; p < PK_ARRAY_SIZE; p++)
    {
        int slotno;
        int comp = strcmp(pk_slot[p].vh.car_no, v_no);
        if (comp == 0)
        {
            slotno = p;

            pk_slot[slotno].occupy = false;
            pk_slot[slotno].vh.parked = false;
            leave_timer(slotno);
            display(slotno);
            printf("vehicle left the park\n");

            break;
        }
    }
}
/* function to calculate the leaving time of the vehicle*/
void leave_timer(int e)
{

    if (pk_slot[e].vh.parked == false)
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        pk_slot[e].vh.out_time.hour = tm.tm_hour;
        pk_slot[e].vh.out_time.minute = tm.tm_min;
    }
}