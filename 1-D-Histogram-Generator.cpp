// Write a code on 1-D Histogarm generator with respect to the given input.dat  file.
// There are 4 columns in the input file. User can arbitrarily choose any 2 of them to generate the histogram.
// Write the histogram in a text file and plot it using gnuplot. Name the text file as output.dat.

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Create a directory to store the output files
    string dirName = "output";
    mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // Read the input file
    ifstream inputFile("input.dat");
    if (!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return 0;
    }

    // Read the first line of the input file to get the number of columns
    string line;
    getline(inputFile, line);
    stringstream ss(line);
    int numColumns = 0;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        numColumns++;
    }

    // Read the second line of the input file to get the number of rows
    getline(inputFile, line);
    ss.str(line);
    ss.clear();
    int numRows = 0;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        numRows++;
    }

    // Read the third line of the input file to get the column names
    getline(inputFile, line);
    ss.str(line);
    ss.clear();
    vector<string> columnNames;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        columnNames.push_back(substr);
    }

    // Read the fourth line of the input file to get the column types
    getline(inputFile, line);
    ss.str(line);
    ss.clear();
    vector<string> columnTypes;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        columnTypes.push_back(substr);
    }

    // Read the fifth line of the input file to get the column units
    getline(inputFile, line);
    ss.str(line);
    ss.clear();
    vector<string> columnUnits;
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        columnUnits.push_back(substr);
    }

    // Read the sixth line of the input file to get the column data
    getline(inputFile, line);
    ss.str(line);
    ss.clear();
    vector<vector<double> > columnData(numColumns);
    for (int i = 0; i < numColumns; i++)
    {
        columnData[i].resize(numRows);
    }
    int row = 0;
    while (ss.good())
    {
        for (int i = 0; i < numColumns; i++)
        {
            string substr;
            getline(ss, substr, ' ');
            columnData[i][row] = stod(substr);
        }
        row++;
    }

    // Close the input file
    inputFile.close();

    // Print the column names, types and units
    cout << "Column Names: ";
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnNames[i] << " ";
    }
    cout << endl;

    cout << "Column Types: ";
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnTypes[i] << " ";
    }
    cout << endl;

    cout << "Column Units: ";
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnUnits[i] << " ";
    }
    cout << endl;

    // Print the column data
    cout << "Column Data: " << endl;
    for (int i = 0; i < numColumns; i++)
    {
        cout << columnNames[i] << ": ";
        for (int j = 0; j < numRows; j++)
        {
            cout << columnData[i][j] << " ";
        }
        cout << endl;
    }

    // Get the column numbers to plot
    int columnNumber1, columnNumber2;
    cout << "Enter the column number to plot (1-" << numColumns << "): ";
    cin >> columnNumber1;
    cout << "Enter the column number to plot (1-" << numColumns << "): ";
    cin >> columnNumber2;

    // Get the number of bins
    int numBins;
    cout << "Enter the number of bins: ";
    cin >> numBins;

    // Get the range of the histogram
    double minRange, maxRange;
    cout << "Enter the minimum range: ";
    cin >> minRange;
    cout << "Enter the maximum range: ";
    cin >> maxRange;

    // Calculate the bin width
    double binWidth = (maxRange - minRange) / numBins;
    
    // Create a vector to store the bin counts
    vector<int> binCounts(numBins);

    // Calculate the bin counts
    for (int i = 0; i < numRows; i++)
    {
        int binNumber = (columnData[columnNumber1 - 1][i] - minRange) / binWidth;
        binCounts[binNumber]++;
    }

    // Print the bin counts
    cout << "Bin Counts: ";
    for (int i = 0; i < numBins; i++)
    {
        cout << binCounts[i] << " ";
    }
    cout << endl;

    // Write the bin counts to a file
    ofstream outputFile("output/output.dat");
    if (!outputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return 0;
    }
    for (int i = 0; i < numBins; i++)
    {
        outputFile << binCounts[i] << endl;
    }
    outputFile.close();

    // Plot the histogram
    string plotCommand = "gnuplot -p -e \"plot 'output/output.dat' with lines\"";
    system(plotCommand.c_str());

    return 0;
}