#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <hdf5.h>
#include <hdf5_hl.h>

#define MODSVFILE      "SVM16_npp_d20030125_t0704334_e0705579_b00014_c20090814190100731372_unkn_SCI.h5" // 0.48 

#define MODSVGRP       "All_Data/VIIRS-M16-SDR_All/"

int main(void){

    /*************************
	 *  Common Declarations  *
     *************************/
	
	hid_t       fileID, dsetID, dspaceID;          /* Handles */
	hid_t		dTypeID;
	herr_t      status;
	hsize_t dimSize[2];
	char dsetName[100];
	int rank, i,j,nRows,nCols;
	int typeIdx;

	htri_t H5_NativeTypes[18] = {
		H5T_NATIVE_CHAR  	,     // char
		H5T_NATIVE_SCHAR 	,     // signed char
		H5T_NATIVE_UCHAR 	,     // unsigned char
		H5T_NATIVE_SHORT 	,     // short
		H5T_NATIVE_USHORT 	,     // unsigned short
		H5T_NATIVE_INT 		,     // int
		H5T_NATIVE_UINT 	,     // unsigned
		H5T_NATIVE_LONG 	,     // long
		H5T_NATIVE_ULONG 	,     // unsigned long
		H5T_NATIVE_LLONG 	,     // long long
		H5T_NATIVE_ULLONG 	,     // unsigned long long
		H5T_NATIVE_FLOAT 	,     // float
		H5T_NATIVE_DOUBLE 	,     // double
		H5T_NATIVE_LDOUBLE 	,     // long double
		H5T_NATIVE_HSIZE 	,     // hsize_t
		H5T_NATIVE_HSSIZE 	,     // hssize_t
		H5T_NATIVE_HERR 	,     // herr_t
		H5T_NATIVE_HBOOL 	      // hbool_t
	};

    /*htri_t nativeType;*/

	// Walk through the types and get their descriptions.
    char *str;
    size_t len;
    typeIdx=0;
    for (typeIdx=0;typeIdx<18;typeIdx++){
        status = H5LTdtype_to_text(H5_NativeTypes[typeIdx], NULL, H5LT_DDL, &len);
        str = (char *) malloc(len * sizeof(char));
        status = H5LTdtype_to_text(H5_NativeTypes[typeIdx], str, H5LT_DDL, &len);
        printf("String description for the type %d: %s\n",typeIdx,str);
        free(str);
    }

    /*exit(0);*/

	// Open the file as Read Only, and default File Access property list
	fileID = H5Fopen(MODSVFILE, H5F_ACC_RDONLY, H5P_DEFAULT);

    /*****************************
	 *  Read in the ModeGran dataset  *
     *****************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"ModeGran");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the ModeGran dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the ModeGran dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of ModeGran dataset : %d\n",rank);
	printf("Dimension sizes of ModeGran dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char ModeGran;

	// Read the ModeGran dataset into the ModeGran array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  &ModeGran);        // Pointer to buffer receiving data

	printf("\nModeGran read status = %d\n",status);

	printf("\nModeGran = ");
	printf (" %4d", ModeGran);
	//printf (" [ ");
	//for (j=0; j<dimSize[0]; j++){
		//printf (" %4d", ModeGran[j]);
	//}
	//printf (" ]\n");

	// Free the ModeGran array pointers

	// HDF Example Method
	//free(ModeGran);

	// Close and release ModeGran dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose ModeGran dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close ModeGran dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the ModeScan dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	/*strcat(dsetName,"ModeScan");*/
	strcat(dsetName,"ModeScan");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the ModeScan dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the ModeScan dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of ModeScan dataset : %d\n",rank);
	printf("Dimension sizes of ModeScan dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	unsigned char *ModeScan = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the ModeScan dataset into the ModeScan array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  ModeScan);        // Pointer to buffer receiving data

	printf("\nModeScan read status = %d\n",status);

	printf("\nModeScan =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", ModeScan[j]);
	}
	printf (" ]\n");

    /*
	 * Free the ModeScan array pointers
     */

	// HDF Example Method
	free(ModeScan);

    /*
	 * Close and release ModeScan dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose ModeScan dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close ModeScan dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the NumberOfBadChecksums dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"NumberOfBadChecksums");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the NumberOfBadChecksums dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the NumberOfBadChecksums dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of NumberOfBadChecksums dataset : %d\n",rank);
	printf("Dimension sizes of NumberOfBadChecksums dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	int *NumberOfBadChecksums = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the NumberOfBadChecksums dataset into the NumberOfBadChecksums array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  NumberOfBadChecksums);        // Pointer to buffer receiving data

	printf("\nNumberOfBadChecksums read status = %d\n",status);

	printf("\nNumberOfBadChecksums =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", NumberOfBadChecksums[j]);
	}
	printf (" ]\n");

	// Free the NumberOfBadChecksums array pointers

	// HDF Example Method
	free(NumberOfBadChecksums);

	// Close and release NumberOfBadChecksums dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose NumberOfBadChecksums dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close NumberOfBadChecksums dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the NumberOfDiscardedPkts dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"NumberOfDiscardedPkts");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the NumberOfDiscardedPkts dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the NumberOfDiscardedPkts dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of NumberOfDiscardedPkts dataset : %d\n",rank);
	printf("Dimension sizes of NumberOfDiscardedPkts dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	int *NumberOfDiscardedPkts = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the NumberOfDiscardedPkts dataset into the NumberOfDiscardedPkts array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  NumberOfDiscardedPkts);        // Pointer to buffer receiving data

	printf("\nNumberOfDiscardedPkts read status = %d\n",status);

	printf("\nNumberOfDiscardedPkts =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", NumberOfDiscardedPkts[j]);
	}
	printf (" ]\n");

	// Free the NumberOfDiscardedPkts array pointers

	// HDF Example Method
	free(NumberOfDiscardedPkts);

	// Close and release NumberOfDiscardedPkts dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose NumberOfDiscardedPkts dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close NumberOfDiscardedPkts dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the NumberOfMissingPkts dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"NumberOfMissingPkts");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the NumberOfMissingPkts dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the NumberOfMissingPkts dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of NumberOfMissingPkts dataset : %d\n",rank);
	printf("Dimension sizes of NumberOfMissingPkts dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	int *NumberOfMissingPkts = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the NumberOfMissingPkts dataset into the NumberOfMissingPkts array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  NumberOfMissingPkts);        // Pointer to buffer receiving data

	printf("\nNumberOfMissingPkts read status = %d\n",status);

	printf("\nNumberOfMissingPkts =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", NumberOfMissingPkts[j]);
	}
	printf (" ]\n");

	// Free the NumberOfMissingPkts array pointers

	// HDF Example Method
	free(NumberOfMissingPkts);

	// Close and release NumberOfMissingPkts dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose NumberOfMissingPkts dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close NumberOfMissingPkts dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


    /*****************************
	 *  Read in the NumberOfScans dataset  *
     *****************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"NumberOfScans");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the NumberOfScans dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

	// Get the datatype ID for this dataset
	dTypeID = H5Dget_type(dsetID);
	// Get the equivalent NATIVE datatype ID
	dTypeID = H5Tget_native_type(dTypeID,H5T_DIR_ASCEND);

	// Determine the index of the desired type
	typeIdx=0;
	for (typeIdx=0;typeIdx<18;typeIdx++){
		if (H5Tequal(dTypeID,H5_NativeTypes[typeIdx])) break;
	}

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the NumberOfScans dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of NumberOfScans dataset : %d\n",rank);
	printf("Dimension sizes of NumberOfScans dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	int NumberOfScans;

	// Read the NumberOfScans dataset into the NumberOfScans array
	status = H5Dread (dsetID,              // dataset ID
					  dTypeID,             // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  &NumberOfScans);        // Pointer to buffer receiving data

	printf("\nNumberOfScans read status = %d\n",status);

	printf("\nNumberOfScans = ");
	printf (" %d", NumberOfScans);

	// Close and release NumberOfScans dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose NumberOfScans dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close NumberOfScans dataspace status = %d\n",status);
	status = H5Tclose (dTypeID);
	printf("Close NumberOfScans datatype status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************
	 *  Read in the PadByte1 dataset  *
     *****************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"PadByte1");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Pad dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Pad dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Pad dataset : %d\n",rank);
	printf("Dimension sizes of Pad dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	unsigned char *PadByte1 = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the Pad dataset into the Pad array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  PadByte1);        // Pointer to buffer receiving data

	printf("\nPadByte1 read status = %d\n",status);

	printf("\nPad =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", PadByte1[j]);
	}
	printf (" ]\n");

    /*
	 * Free the Pad array pointers
     */

	// HDF Example Method
	free(PadByte1);

    /*
	 * Close and release Pad dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose Pad dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Pad dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


    /*****************************************
	 *  Read in the QF1_VIIRSI1SDR dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"QF1_VIIRSMBANDSDR");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF1_VIIRSI1SDR dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF1_VIIRSI1SDR dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF1_VIIRSMBANDSDR dataset : %d\n",rank);
	printf("Dimension sizes of QF1_VIIRSMBANDSDR dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);
    nRows = dimSize[0];
    nCols = dimSize[1];

	// Allocate memory for our array

	// HDF5 example method
	unsigned char **QF1_VIIRSMBANDSDR = (unsigned char **) malloc(nRows * sizeof(unsigned char *));
	QF1_VIIRSMBANDSDR[0] = (unsigned char *) malloc(nRows * nCols * sizeof(unsigned char));
	for (i=1; i<nRows; i++)
		QF1_VIIRSMBANDSDR[i] = QF1_VIIRSMBANDSDR[0] + i * nCols;

	 //Test Method 1
	//int **QF1_VIIRSI1SDR = malloc(nRows * sizeof(int *));
	//for(i = 0; i < nRows; i++)
		//QF1_VIIRSI1SDR[i] = malloc(nCols * sizeof(int));

	 //Test Method 2
	//int **QF1_VIIRSI1SDR = malloc(nRows * sizeof(int *));
	//QF1_VIIRSI1SDR[0] = malloc(nRows * nCols * sizeof(int));
	//for(i = 1; i < nRows; i++)
		//QF1_VIIRSI1SDR[i] = QF1_VIIRSI1SDR[0] + i * nCols;



	// Read the QF1_VIIRSI1SDR dataset into the QF1_VIIRSI1SDR array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF1_VIIRSMBANDSDR[0]);        // Pointer to buffer receiving data

	printf("\nQF1_VIIRSMBANDSDR read status = %d\n",status);


	printf("\nQF1_VIIRSMBANDSDR =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", QF1_VIIRSMBANDSDR[i][j]);
			//printf (" %4d", *(QF1_VIIRSMBANDSDR[i] + j));
		}
		printf (" ]\n");
	}

    // Free the QF1_VIIRSMBANDSDR array pointers

	// HDF Example Method
	free(QF1_VIIRSMBANDSDR[0]);
	free(QF1_VIIRSMBANDSDR);

	// Test Method 1
	//for(i = 0; i < nRows; i++)
		//free((void *)QF1_VIIRSI1SDR[i]);
	//free((void *)QF1_VIIRSI1SDR);

	// Test Method 2
	//free((void *)QF1_VIIRSI1SDR[0]);
	//free((void *)QF1_VIIRSI1SDR);

    /*
	 * Close and release QF1_VIIRSI1SDR dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF1_VIIRSMBANDSDR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF1_VIIRSMBANDSDR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF2_SCAN_SDR dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"QF2_SCAN_SDR");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF2_SCAN_SDR dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF2_SCAN_SDR dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF2_SCAN_SDR dataset : %d\n",rank);
	printf("Dimension sizes of QF2_SCAN_SDR dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char *QF2_SCAN_SDR = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the QF2_SCAN_SDR dataset into the QF2_SCAN_SDR array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF2_SCAN_SDR);        // Pointer to buffer receiving data

	printf("\nQF2_SCAN_SDR read status = %d\n",status);

	printf("\nQF2_SCAN_SDR =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", QF2_SCAN_SDR[j]);
	}
	printf (" ]\n");

    /*
	 * Free the QF2_SCAN_SDR array pointers
     */

	// HDF Example Method
	free(QF2_SCAN_SDR);

    /*
	 * Close and release QF2_SCAN_SDR dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF2_SCAN_SDR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF2_SCAN_SDR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF3_SCAN_RDR dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"QF3_SCAN_RDR");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF3_SCAN_RDR dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF3_SCAN_RDR dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF3_SCAN_RDR dataset : %d\n",rank);
	printf("Dimension sizes of QF3_SCAN_RDR dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char *QF3_SCAN_RDR = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the QF3_SCAN_RDR dataset into the QF3_SCAN_RDR array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF3_SCAN_RDR);        // Pointer to buffer receiving data

	printf("\nQF3_SCAN_RDR read status = %d\n",status);

	printf("\nQF3_SCAN_RDR =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", QF3_SCAN_RDR[j]);
	}
	printf (" ]\n");

    /*
	 * Free the QF3_SCAN_RDR array pointers
     */

	// HDF Example Method
	free(QF3_SCAN_RDR);

    /*
	 * Close and release QF3_SCAN_RDR dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF3_SCAN_RDR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF3_SCAN_RDR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF4_SCAN_SDR dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"QF4_SCAN_SDR");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF4_SCAN_SDR dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF4_SCAN_SDR dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF4_SCAN_SDR dataset : %d\n",rank);
	printf("Dimension sizes of QF4_SCAN_SDR dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char *QF4_SCAN_SDR = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the QF4_SCAN_SDR dataset into the QF4_SCAN_SDR array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF4_SCAN_SDR);        // Pointer to buffer receiving data

	printf("\nQF4_SCAN_SDR read status = %d\n",status);

	printf("\nQF4_SCAN_SDR =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", QF4_SCAN_SDR[j]);
	}
	printf (" ]\n");

    /*
	 * Free the QF4_SCAN_SDR array pointers
     */

	// HDF Example Method
	free(QF4_SCAN_SDR);

    /*
	 * Close and release QF4_SCAN_SDR dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF4_SCAN_SDR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF4_SCAN_SDR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF5_GRAN_BADDETECTOR dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"QF5_GRAN_BADDETECTOR");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF5_GRAN_BADDETECTOR dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF5_GRAN_BADDETECTOR dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF5_GRAN_BADDETECTOR dataset : %d\n",rank);
	printf("Dimension sizes of QF5_GRAN_BADDETECTOR dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char *QF5_GRAN_BADDETECTOR = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the QF5_GRAN_BADDETECTOR dataset into the QF5_GRAN_BADDETECTOR array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF5_GRAN_BADDETECTOR);        // Pointer to buffer receiving data

	printf("\nQF5_GRAN_BADDETECTOR read status = %d\n",status);

	printf("\nQF5_GRAN_BADDETECTOR =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", QF5_GRAN_BADDETECTOR[j]);
	}
	printf (" ]\n");

    /*
	 * Free the QF5_GRAN_BADDETECTOR array pointers
     */

	// HDF Example Method
	free(QF5_GRAN_BADDETECTOR);

    /*
	 * Close and release QF5_GRAN_BADDETECTOR dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF5_GRAN_BADDETECTOR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF5_GRAN_BADDETECTOR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


    /*****************************************
	 *  Read in the Radiance dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"Radiance");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Radiance dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Radiance dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Radiance dataset : %d\n",rank);
	printf("Dimension sizes of Radiance dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);
    nRows = dimSize[0];
    nCols = dimSize[1];

	// Allocate memory for our array

	// HDF5 example method
	unsigned short **Radiance = (unsigned short **) malloc(nRows * sizeof(unsigned short *));
	Radiance[0] = (unsigned short *) malloc(nRows * nCols * sizeof(unsigned short));
	for (i=1; i<nRows; i++)
		Radiance[i] = Radiance[0] + i * nCols;

	 //Test Method 1
	//int **Radiance = malloc(nRows * sizeof(int *));
	//for(i = 0; i < nRows; i++)
		//Radiance[i] = malloc(nCols * sizeof(int));

	 //Test Method 2
	//int **Radiance = malloc(nRows * sizeof(int *));
	//Radiance[0] = malloc(nRows * nCols * sizeof(int));
	//for(i = 1; i < nRows; i++)
		//Radiance[i] = Radiance[0] + i * nCols;



	// Read the Radiance dataset into the Radiance array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_USHORT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  Radiance[0]);        // Pointer to buffer receiving data

	printf("\nRadiance read status = %d\n",status);


	printf("\nRadiance =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", Radiance[i][j]);
			//printf (" %4d", *(Radiance[i] + j));
		}
		printf (" ]\n");
	}


	// Free the Radiance array pointers

	// HDF Example Method
	//free(Radiance[0]);
	//free(Radiance);

	// Test Method 1
	//for(i = 0; i < nRows; i++)
		//free((void *)Radiance[i]);
	//free((void *)Radiance);

	// Test Method 2
	//free((void *)Radiance[0]);
	//free((void *)Radiance);


	// Close and release HDF5 Radiance dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose Radiance dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Radiance dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the RadianceFactors dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"RadianceFactors");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the RadianceFactors dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the RadianceFactors dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of RadianceFactors dataset : %d\n",rank);
	printf("Dimension sizes of RadianceFactors dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	float *RadianceFactors = (float *) malloc(dimSize[0] * sizeof(float));

	// Read the RadianceFactors dataset into the RadianceFactors array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  RadianceFactors);        // Pointer to buffer receiving data

	printf("\nRadianceFactors read status = %d\n",status);

	printf("\nRadianceFactors =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %11.6f", RadianceFactors[j]);
	}
	printf (" ]\n");


	// Free the RadianceFactors array pointers

	// HDF Example Method
	//free(RadianceFactors);

	// Close and release RadianceFactors dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose RadianceFactors dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close RadianceFactors dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	// Allocate the array memory for the scaled Reflectances
	float **Radiance_scaled = (float **) malloc(nRows * sizeof(float *));
	Radiance_scaled[0] = (float *) malloc(nRows * nCols * sizeof(float));
	for (i=1; i<nRows; i++)
		Radiance_scaled[i] = Radiance_scaled[0] + i * nCols;

	for (i=0; i<nRows; i++) {
		for (j=0; j<nCols; j++){
			Radiance_scaled[i][j] = (float)Radiance[i][j]*RadianceFactors[0]
				+ (float)RadianceFactors[1];
		}
	}
	printf("\nRadiance (scaled) =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", Radiance_scaled[i][j]);
		}
		printf (" ]\n");
	}

	free(Radiance[0]);
	free(Radiance);

	free(RadianceFactors);
	
    free(Radiance_scaled[0]);
	free(Radiance_scaled);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the BrightnessTemperature dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"BrightnessTemperature");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the BrightnessTemperature dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the BrightnessTemperature dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of BrightnessTemperature dataset : %d\n",rank);
	printf("Dimension sizes of BrightnessTemperature dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);
    nRows = dimSize[0];
    nCols = dimSize[1];

	// Allocate memory for our array

	// HDF5 example method
	unsigned short **BrightnessTemperature = (unsigned short **) malloc(nRows * sizeof(unsigned short *));
	BrightnessTemperature[0] = (unsigned short *) malloc(nRows * nCols * sizeof(unsigned short));
	for (i=1; i<nRows; i++)
		BrightnessTemperature[i] = BrightnessTemperature[0] + i * nCols;

	 //Test Method 1
	//unsigned short **BrightnessTemperature = malloc(dimSize[0] * sizeof(unsigned short *));
	//for(i = 0; i < dimSize[0]; i++)
		//BrightnessTemperature[i] = malloc(dimSize[1] * sizeof(unsigned short));

	 //Test Method 2
	//unsigned short **BrightnessTemperature = malloc(dimSize[0] * sizeof(unsigned short *));
	//BrightnessTemperature[0] = malloc(dimSize[0] * dimSize[1] * sizeof(unsigned short));
	//for(i = 1; i < dimSize[0]; i++)
		//BrightnessTemperature[i] = BrightnessTemperature[0] + i * dimSize[1];

	// Read the BrightnessTemperature dataset into the BrightnessTemperature array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_USHORT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  BrightnessTemperature[0]);        // Pointer to buffer receiving data

	printf("\nBrightnessTemperature read status = %d\n",status);


	printf("\nBrightnessTemperature =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", BrightnessTemperature[i][j]);
			//printf (" %4d", *(BrightnessTemperature[i] + j));
		}
		printf (" ]\n");
	}

	// Free the BrightnessTemperature array pointers

	// HDF Example Method
    /*free(BrightnessTemperature[0]);*/
    /*free(BrightnessTemperature);*/

	// Test Method 1
	//for(i = 0; i < dimSize[0]; i++)
		//free((void *)BrightnessTemperature[i]);
	//free((void *)BrightnessTemperature);

	// Test Method 2
	//free((void *)BrightnessTemperature[0]);
	//free((void *)BrightnessTemperature);

	// Close and release HDF5 BrightnessTemperature dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose BrightnessTemperature dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close BrightnessTemperature dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the BrightnessTemperatureFactors dataset  *
     *****************************************/

	strcpy(dsetName,MODSVGRP);
	strcat(dsetName,"BrightnessTemperatureFactors");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the BrightnessTemperatureFactors dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the BrightnessTemperatureFactors dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of BrightnessTemperatureFactors dataset : %d\n",rank);
	printf("Dimension sizes of BrightnessTemperatureFactors dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	float *BrightnessTemperatureFactors = (float *) malloc(dimSize[0] * sizeof(float));

	// Read the BrightnessTemperatureFactors dataset into the BrightnessTemperatureFactors array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  BrightnessTemperatureFactors);        // Pointer to buffer receiving data

	printf("\nBrightnessTemperatureFactors read status = %d\n",status);

	printf("\nBrightnessTemperatureFactors =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %11.6f", BrightnessTemperatureFactors[j]);
	}
	printf (" ]\n");

	// Free the BrightnessTemperatureFactors array pointers

	// HDF Example Method
	//free(BrightnessTemperatureFactors);

	// Close and release BrightnessTemperatureFactors dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose BrightnessTemperatureFactors dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close BrightnessTemperatureFactors dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	// Allocate the array memory for the scaled BrightnessTemperatures
	float **BrightnessTemperature_scaled = (float **) malloc(nRows * sizeof(float *));
	BrightnessTemperature_scaled[0] = (float *) malloc(nRows * nCols * sizeof(float));
	for (i=1; i<nRows; i++)
		BrightnessTemperature_scaled[i] = BrightnessTemperature_scaled[0] + i * nCols;

	// Generate the scaled BrightnessTemperatures
	for (i=0; i<nRows; i++) {
		for (j=0; j<nCols; j++){
			BrightnessTemperature_scaled[i][j] = (float)BrightnessTemperature[i][j]*BrightnessTemperatureFactors[0]
				+ (float)BrightnessTemperatureFactors[1];
		}
	}
    printf("\nBrightnessTemperature (scaled) =\n");
    for (i=0; i<10; i++) {
        printf (" [ ");
        for (j=0; j<10; j++){
            printf (" %11.6f", BrightnessTemperature_scaled[i][j]);
        }
        printf (" ]\n");
    }

	free(BrightnessTemperature[0]);
	free(BrightnessTemperature);

	free(BrightnessTemperatureFactors);

	free(BrightnessTemperature_scaled[0]);
	free(BrightnessTemperature_scaled);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /****************************
	 *  Clean up for this file  *
     ****************************/

	// Close and release file.
	status = H5Fclose (fileID);


	return 0;
}
