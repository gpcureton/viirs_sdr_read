#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <hdf5.h>
#include <hdf5_hl.h>

#define IMGSVFILE      "SVI01_npp_d20030125_t0704334_e0705579_b00014_c20090823223722753350_unkn_SCI.h5" // 0.48

#define IMGSVGRP       "All_Data/VIIRS-I1-SDR_All/"

int main(void){

    /*************************
	 *  Common Declarations  *
     *************************/
	
	hid_t       fileID, dsetID, dspaceID;          /* Handles */
	hid_t		dTypeID;
	herr_t      status;
	hsize_t dimSize[2];
	char dsetName[100];
	int rank,i,j,nRows,nCols;
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

	// Open the file as Read Only, and default File Access property list
	fileID = H5Fopen(IMGSVFILE, H5F_ACC_RDONLY, H5P_DEFAULT);

    /*****************************
	 *  Read in the ModeGran dataset  *
     *****************************/

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	// Allocate memory for our array

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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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
	printf (" %4d", NumberOfScans);

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

	strcpy(dsetName,IMGSVGRP);
	strcat(dsetName,"PadByte1");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the PadByte1 dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the PadByte1 dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of PadByte1 dataset : %d\n",rank);
	printf("Dimension sizes of PadByte1 dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	unsigned char *PadByte1 = (unsigned char *) malloc(dimSize[0] * sizeof(unsigned char));

	// Read the PadByte1 dataset into the PadByte1 array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_UCHAR,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  PadByte1);        // Pointer to buffer receiving data

	printf("\nPadByte1 read status = %d\n",status);

	printf("\nPadByte1 =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", PadByte1[j]);
	}
	printf (" ]\n");

	// Free the PadByte1 array pointers

	// HDF Example Method
	free(PadByte1);

	// Close and release PadByte1 dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose PadByte1 dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close PadByte1 dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


    /*****************************************
	 *  Read in the QF1_VIIRSI1SDR dataset  *
     *****************************************/

	strcpy(dsetName,IMGSVGRP);
	strcat(dsetName,"QF1_VIIRSIBANDSDR");
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

	printf("Rank of QF1_VIIRSIBANDSDR dataset : %d\n",rank);
	printf("Dimension sizes of QF1_VIIRSIBANDSDR dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);
    nRows = dimSize[0];
    nCols = dimSize[1];

	// Allocate memory for our array

	// HDF5 example method
	unsigned char **QF1_VIIRSIBANDSDR = (unsigned char **) malloc(nRows * sizeof(unsigned char *));
	QF1_VIIRSIBANDSDR[0] = (unsigned char *) malloc(nRows * nCols * sizeof(unsigned char));
	for (i=1; i<nRows; i++)
		QF1_VIIRSIBANDSDR[i] = QF1_VIIRSIBANDSDR[0] + i * nCols;

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
					  QF1_VIIRSIBANDSDR[0]);        // Pointer to buffer receiving data

	printf("\nQF1_VIIRSIBANDSDR read status = %d\n",status);


	printf("\nQF1_VIIRSIBANDSDR =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", QF1_VIIRSIBANDSDR[i][j]);
			//printf (" %4d", *(QF1_VIIRSIBANDSDR[i] + j));
		}
		printf (" ]\n");
	}

    // Free the QF1_VIIRSIBANDSDR array pointers

	// HDF Example Method
	free(QF1_VIIRSIBANDSDR[0]);
	free(QF1_VIIRSIBANDSDR);

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
	printf("\n\nClose QF1_VIIRSIBANDSDR dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF1_VIIRSIBANDSDR dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF2_SCAN_SDR dataset  *
     *****************************************/

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	strcpy(dsetName,IMGSVGRP);
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

	// Allocate the array memory for the scaled Radiances
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
	 *  Read in the Reflectance dataset  *
     *****************************************/

	strcpy(dsetName,IMGSVGRP);
	strcat(dsetName,"Reflectance");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Reflectance dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Reflectance dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Reflectance dataset : %d\n",rank);
	printf("Dimension sizes of Reflectance dataset : ");
	for (i=0;i<rank;i++)
        printf("%llu\t",dimSize[i]);
    nRows = dimSize[0];
    nCols = dimSize[1];

	// Allocate memory for our array

	// HDF5 example method
	unsigned short **Reflectance = (unsigned short **) malloc(nRows * sizeof(unsigned short *));
	Reflectance[0] = (unsigned short *) malloc(nRows * nCols * sizeof(unsigned short));
	for (i=1; i<nRows; i++)
		Reflectance[i] = Reflectance[0] + i * nCols;

	 //Test Method 1
	//unsigned short **Reflectance = malloc(dimSize[0] * sizeof(unsigned short *));
	//for(i = 0; i < dimSize[0]; i++)
		//Reflectance[i] = malloc(dimSize[1] * sizeof(unsigned short));

	 //Test Method 2
	//unsigned short **Reflectance = malloc(dimSize[0] * sizeof(unsigned short *));
	//Reflectance[0] = malloc(dimSize[0] * dimSize[1] * sizeof(unsigned short));
	//for(i = 1; i < dimSize[0]; i++)
		//Reflectance[i] = Reflectance[0] + i * dimSize[1];

	// Read the Reflectance dataset into the Reflectance array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_USHORT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  Reflectance[0]);        // Pointer to buffer receiving data

	printf("\nReflectance read status = %d\n",status);


	printf("\nReflectance =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", Reflectance[i][j]);
			//printf (" %4d", *(Reflectance[i] + j));
		}
		printf (" ]\n");
	}

	// Free the Reflectance array pointers

	// HDF Example Method
    /*free(Reflectance[0]);*/
    /*free(Reflectance);*/

	// Test Method 1
	//for(i = 0; i < dimSize[0]; i++)
		//free((void *)Reflectance[i]);
	//free((void *)Reflectance);

	// Test Method 2
	//free((void *)Reflectance[0]);
	//free((void *)Reflectance);

	// Close and release HDF5 Reflectance dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose Reflectance dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Reflectance dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the ReflectanceFactors dataset  *
     *****************************************/

	strcpy(dsetName,IMGSVGRP);
	strcat(dsetName,"ReflectanceFactors");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the ReflectanceFactors dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the ReflectanceFactors dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of ReflectanceFactors dataset : %d\n",rank);
	printf("Dimension sizes of ReflectanceFactors dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

	// Allocate memory for our array

	float *ReflectanceFactors = (float *) malloc(dimSize[0] * sizeof(float));

	// Read the ReflectanceFactors dataset into the ReflectanceFactors array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  ReflectanceFactors);        // Pointer to buffer receiving data

	printf("\nReflectanceFactors read status = %d\n",status);

	printf("\nReflectanceFactors =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %11.6f", ReflectanceFactors[j]);
	}
	printf (" ]\n");

	// Free the ReflectanceFactors array pointers

	// HDF Example Method
	//free(ReflectanceFactors);

	// Close and release ReflectanceFactors dataset and dataspace
	status = H5Dclose (dsetID);
	printf("\n\nClose ReflectanceFactors dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close ReflectanceFactors dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	// Allocate the array memory for the scaled Reflectances
	float **Reflectance_scaled = (float **) malloc(nRows * sizeof(float *));
	Reflectance_scaled[0] = (float *) malloc(nRows * nCols * sizeof(float));
	for (i=1; i<nRows; i++)
		Reflectance_scaled[i] = Reflectance_scaled[0] + i * nCols;

	// Generate the scaled Reflectances
	for (i=0; i<nRows; i++) {
		for (j=0; j<nCols; j++){
			Reflectance_scaled[i][j] = (float)Reflectance[i][j]*ReflectanceFactors[0]
				+ (float)ReflectanceFactors[1];
		}
	}
    printf("\nReflectance (scaled) =\n");
    for (i=0; i<10; i++) {
        printf (" [ ");
        for (j=0; j<10; j++){
            printf (" %11.6f", Reflectance_scaled[i][j]);
        }
        printf (" ]\n");
    }

	free(Reflectance[0]);
	free(Reflectance);

	free(ReflectanceFactors);

	free(Reflectance_scaled[0]);
	free(Reflectance_scaled);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");



    /****************************
	 *  Clean up for this file  *
     ****************************/

	// Close and release file.
	status = H5Fclose (fileID);


	return 0;
}
