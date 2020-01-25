//-----------------------------------------------------------------------------
// SimulationStub.c
// # Baladithya Balamurugan
// # CruzId: bbalamur
// # Class: CSE-15-1
// # Date: 12/03/19
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Job.h"
#include "IntegerQueue.h"

//-----------------------------------------------------------------------------
// The following function may be of use in assembling the initial backup array.
// You may use it as is, alter it as you see fit, or delete it altogether.
//-----------------------------------------------------------------------------

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE *in)
{
    int a, d;
    fscanf(in, "%d %d\n", &a, &d);
    return newJob(a, d);
}

//-----------------------------------------------------------------------------
// The following stub for function main() contains a possible algorithm for
// this project.  Follow it if you like.  Note that there are no instructions
// included below for writing to either of the output files.  You must
// intersperse those commands as necessary.
//-----------------------------------------------------------------------------

int shortestProcQueue(IntegerQueue *processorQueue, int currentNumProcs)
{
    int shortestQueue = 1;
    for (int i = 1; i <= currentNumProcs; i++)
    {
        // printf("Length of Processor %d: %d\n", i, length(processorQueue[i]));
        if (length(processorQueue[i]) < length(processorQueue[shortestQueue]))
        {
            shortestQueue = i;
        }
    }
    //printf("Shortest Queue: %d\n", shortestQueue);
    return shortestQueue;
}

int TotalWait(IntegerQueue *processorQueue, Job *BAK, int m)
{
    int TotalWaitTime = 0;
    for (int i = 0; i < m; i++)
    {
        int temp = dequeue(processorQueue[0]);
        TotalWaitTime += getWaitTime(BAK[temp]);
        enqueue(processorQueue[0], temp);
    }
    return TotalWaitTime;
}

int MaxWait(IntegerQueue *processorQueue, Job *BAK, int m)
{
    int MaxWaitTime = 0;
    for (int i = 0; i < m; i++)
    {
        int temp = dequeue(processorQueue[0]);
        if (getWaitTime(BAK[temp]) > MaxWaitTime)
            MaxWaitTime = getWaitTime(BAK[temp]);
        enqueue(processorQueue[0], temp);
    }
    return MaxWaitTime;
}

void resetProcQueue(IntegerQueue *processorQueue, Job *BAK, int m)
{
    if (!isEmpty(processorQueue[0]))
        dequeueAll(processorQueue[0]);

    for (int i = 0; i < m; i++)
        resetFinishTime(BAK[i]);
}

int finitoProcess(IntegerQueue *processorQueue, Job *BAK, int time, int currentNumProcs)
{
    for (int i = 1; i <= currentNumProcs; i++)
    {
        if (!isEmpty(processorQueue[i]))
        {
            if (getFinish(BAK[peek(processorQueue[i])]) == time)
            {
                enqueue(processorQueue[0], dequeue(processorQueue[i]));
                if (!isEmpty(processorQueue[i]))
                    computeFinishTime(BAK[peek(processorQueue[i])], time);
                return 1;
            }
        }
    }
    return 0;
}

int newProcess(IntegerQueue *processorQueue, Job *BAK, int time, int currentNumProcs)
{
    if (!isEmpty(processorQueue[0]))
    {
        if (getArrival(BAK[peek(processorQueue[0])]) == time)
        {
            int temp = dequeue(processorQueue[0]);
            int idx = shortestProcQueue(processorQueue, currentNumProcs);
            enqueue(processorQueue[idx], temp);
            if (getFinish(BAK[peek(processorQueue[idx])]) == UNDEF)
                computeFinishTime(BAK[peek(processorQueue[idx])], time);
            return 1;
        }
    }
    return 0;
}

// main()
int main(int argc, char *argv[])
{
    FILE *fi, *foTrc, *foRpt;
    if (argc != 2)
    {
        printf("Usage: %s input-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fi = fopen(argv[1], "r+")) == NULL)
    {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    char *traceFilename = calloc(strlen(argv[1]) + 4, sizeof(char));
    char *reportFilename = calloc(strlen(argv[1]) + 4, sizeof(char));
    strcat(traceFilename, argv[1]);
    strcat(reportFilename, argv[1]);
    strcat(traceFilename, ".trc");
    strcat(reportFilename, ".rpt");
    if ((foTrc = fopen(traceFilename, "w+")) == NULL)
    {
        printf("Unable to write to file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((foRpt = fopen(reportFilename, "w+")) == NULL)
    {
        printf("Unable to write to file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    rewind(fi);

    fprintf(foTrc, "Trace file: %s\n", traceFilename);
    fprintf(foRpt, "Report file: %s\n", reportFilename);

    int m;
    if (fscanf(fi, "%d", &m) != 0)
    {
        fprintf(foTrc, "%d Jobs:\n", m);
        fprintf(foRpt, "%d Jobs:\n", m);
    }
    Job *BAK = calloc(m, sizeof(Job));
    for (int i = 0; i < m; i++)
    {
        BAK[i] = getJob(fi);
        printJob(foTrc, BAK[i]);
        printJob(foRpt, BAK[i]);
    }
    fprintf(foTrc, "\n");
    fprintf(foRpt, "\n\n***********************************************************\n");

    IntegerQueue *processorQueue = calloc(m, sizeof(IntegerQueue));
    for (int i = 0; i < m; i++)
        processorQueue[i] = newIntegerQueue();

    for (int currentNumProcs = 1; currentNumProcs < m; currentNumProcs++)
    {
        // fprintf(foTrc, "storage queue: %s\n", IntegerQueueToString(processorQueue[0]));
        for (int i = 0; i < m; i++)
            enqueue(processorQueue[0], i);
        if (currentNumProcs == 1)
        {
            fprintf(foTrc, "*****************************\n%d processor:\n*****************************\n", currentNumProcs);
            fprintf(foRpt, "%d processor: ", currentNumProcs);
        }
        else
        {
            fprintf(foTrc, "*****************************\n%d processors:\n*****************************\n", currentNumProcs);
            fprintf(foRpt, "%d processors: ", currentNumProcs);
        }
        // fprintf(foTrc, "storage queue: %s\n", IntegerQueueToString(processorQueue[0]));
        int time = 0;
        int jobsRemain = m;
        int printable = 1;
        while (jobsRemain > 0)
        {
            while (finitoProcess(processorQueue, BAK, time, currentNumProcs))
            {
                printable = 1;
                jobsRemain--;
            }
            while (newProcess(processorQueue, BAK, time, currentNumProcs))
                printable = 1;

            if (printable)
            {
                fprintf(foTrc, "time=%d\n", time);
                for (int i = 0; i <= currentNumProcs; i++)
                {
                    fprintf(foTrc, "%d: ", i);
                    for (int j = 0; j < length(processorQueue[i]); j++)
                    {
                        int temp = dequeue(processorQueue[i]);
                        printJob(foTrc, BAK[temp]);
                        enqueue(processorQueue[i], temp);
                    }
                    fprintf(foTrc, "\n");
                }
                fprintf(foTrc, "\n");
            }
            time++;
            printable = 0;
        }

        fprintf(foRpt, "totalWait=%d, maxWait=%d, averageWait=%.2f\n", TotalWait(processorQueue, BAK, m), MaxWait(processorQueue, BAK, m), (float)((float)TotalWait(processorQueue, BAK, m) / (float)m));
        resetProcQueue(processorQueue, BAK, m);
    }
    for (int i = 0; i < m; i++)
    {
        freeIntegerQueue(&processorQueue[i]);
        freeJob(&BAK[i]);
    }
    free(traceFilename);
    free(reportFilename);
    free(BAK);
    free(processorQueue);
    fclose(fi);
    fclose(foRpt);
    fclose(foTrc);
    return EXIT_SUCCESS;
}
