#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <hdf5.h>


#define IMGGEOFILE "GIMGO_npp_d20030125_t0704334_e0705579_b00014_c20090823223722753834_unkn_SCI.h5"  // 0.48 

#define IMGGEOGRP       "All_Data/VIIRS-IMG-GEO_All/"

int main(void){

    /*************************
	 *  Common Declarations  *
     *************************/
	
	hid_t       fileID, dsetID, dspaceID;          /* Handles */
	herr_t      status;
	hsize_t dimSize[2];
	char dsetName[100];
	int rank, i,j;

	// Open the file as Read Only, and default File Access property list
	fileID = H5Fopen(IMGGEOFILE, H5F_ACC_RDONLY, H5P_DEFAULT);

    /**********************************
	 *  Read in the Latitude dataset  *
     **********************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"Latitude");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Latitude dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Latitude dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Latitude dataset : %d\n",rank);
	printf("Dimension sizes of Latitude dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **Latitude = (float **) malloc(dimSize[0] * sizeof(float *));
	Latitude[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		Latitude[i] = Latitude[0] + i * dimSize[1];

	// Read the Latitude dataset into the Latitude array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  Latitude[0]);        // Pointer to buffer receiving data

	printf("\nLatitude read status = %d\n",status);


	printf("\nLatitude =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", Latitude[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the Latitude array pointers
     */

	// HDF Example Method
	free(Latitude[0]);
	free(Latitude);

    /*
	 * Close and release Latitude dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose Latitude dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Latitude dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /**********************************
	 *  Read in the Longitude dataset  *
     **********************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"Longitude");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Longitude dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Longitude dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Longitude dataset : %d\n",rank);
	printf("Dimension sizes of Longitude dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **Longitude = (float **) malloc(dimSize[0] * sizeof(float *));
	Longitude[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		Longitude[i] = Longitude[0] + i * dimSize[1];

	// Read the Longitude dataset into the Longitude array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  Longitude[0]);       // Pointer to buffer receiving data

	printf("\nLongitude read status = %d\n",status);

	printf("\nLongitude =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", Longitude[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the Longitude array pointers
     */

	// HDF Example Method
	free(Longitude[0]);
	free(Longitude);

    /*
	 * Close and release Longitude dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose Longitude dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Longitude dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SatelliteAzimuthAngle dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"SatelliteAzimuthAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SatelliteAzimuthAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SatelliteAzimuthAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SatelliteAzimuthAngle dataset : %d\n",rank);
	printf("Dimension sizes of SatelliteAzimuthAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SatelliteAzimuthAngle = (float **) malloc(dimSize[0] * sizeof(float *));
	SatelliteAzimuthAngle[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SatelliteAzimuthAngle[i] = SatelliteAzimuthAngle[0] + i * dimSize[1];

	// Read the SatelliteAzimuthAngle dataset into the SatelliteAzimuthAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SatelliteAzimuthAngle[0]);        // Pointer to buffer receiving data

	printf("\nSatelliteAzimuthAngle read status = %d\n",status);


	printf("\nSatelliteAzimuthAngle =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", SatelliteAzimuthAngle[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SatelliteAzimuthAngle array pointers
     */

	// HDF Example Method
	free(SatelliteAzimuthAngle[0]);
	free(SatelliteAzimuthAngle);

    /*
	 * Close and release SatelliteAzimuthAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SatelliteAzimuthAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SatelliteAzimuthAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SatelliteZenithAngle dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"SatelliteZenithAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SatelliteZenithAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SatelliteZenithAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SatelliteZenithAngle dataset : %d\n",rank);
	printf("Dimension sizes of SatelliteZenithAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SatelliteZenithAngle = (float **) malloc(dimSize[0] * sizeof(float *));
	SatelliteZenithAngle[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SatelliteZenithAngle[i] = SatelliteZenithAngle[0] + i * dimSize[1];

	// Read the SatelliteZenithAngle dataset into the SatelliteZenithAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SatelliteZenithAngle[0]);        // Pointer to buffer receiving data

	printf("\nSatelliteZenithAngle read status = %d\n",status);


	printf("\nSatelliteZenithAngle =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", SatelliteZenithAngle[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SatelliteZenithAngle array pointers
     */

	// HDF Example Method
	free(SatelliteZenithAngle[0]);
	free(SatelliteZenithAngle);

    /*
	 * Close and release SatelliteZenithAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SatelliteZenithAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SatelliteZenithAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SolarAzimuthAngle dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"SolarAzimuthAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SolarAzimuthAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SolarAzimuthAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SolarAzimuthAngle dataset : %d\n",rank);
	printf("Dimension sizes of SolarAzimuthAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SolarAzimuthAngle = (float **) malloc(dimSize[0] * sizeof(float *));
	SolarAzimuthAngle[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SolarAzimuthAngle[i] = SolarAzimuthAngle[0] + i * dimSize[1];

	// Read the SolarAzimuthAngle dataset into the SolarAzimuthAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SolarAzimuthAngle[0]);        // Pointer to buffer receiving data

	printf("\nSolarAzimuthAngle read status = %d\n",status);


	printf("\nSolarAzimuthAngle =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", SolarAzimuthAngle[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SolarAzimuthAngle array pointers
     */

	// HDF Example Method
	free(SolarAzimuthAngle[0]);
	free(SolarAzimuthAngle);

    /*
	 * Close and release SolarAzimuthAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SolarAzimuthAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SolarAzimuthAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SolarZenithAngle dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"SolarZenithAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SolarZenithAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SolarZenithAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SolarZenithAngle dataset : %d\n",rank);
	printf("Dimension sizes of SolarZenithAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SolarZenithAngle = (float **) malloc(dimSize[0] * sizeof(float *));
	SolarZenithAngle[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SolarZenithAngle[i] = SolarZenithAngle[0] + i * dimSize[1];

	// Read the SolarZenithAngle dataset into the SolarZenithAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SolarZenithAngle[0]);        // Pointer to buffer receiving data

	printf("\nSolarZenithAngle read status = %d\n",status);


	printf("\nSolarZenithAngle =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", SolarZenithAngle[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SolarZenithAngle array pointers
     */

	// HDF Example Method
	free(SolarZenithAngle[0]);
	free(SolarZenithAngle);

    /*
	 * Close and release SolarZenithAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SolarZenithAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SolarZenithAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the Height dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"Height");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the Height dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the Height dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of Height dataset : %d\n",rank);
	printf("Dimension sizes of Height dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **Height = (float **) malloc(dimSize[0] * sizeof(float *));
	Height[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		Height[i] = Height[0] + i * dimSize[1];

	 //Test Method 1
	//float **Height = malloc(dimSize[0] * sizeof(float *));
	//for(i = 0; i < dimSize[0]; i++)
		//Height[i] = malloc(dimSize[1] * sizeof(float));

	 //Test Method 2
	//float **Height = malloc(dimSize[0] * sizeof(float *));
	//Height[0] = malloc(dimSize[0] * dimSize[1] * sizeof(float));
	//for(i = 1; i < dimSize[0]; i++)
		//Height[i] = Height[0] + i * dimSize[1];

	// Read the Height dataset into the Height array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  Height[0]);          // Pointer to buffer receiving data

	printf("\nHeight read status = %d\n",status);


	printf("\nHeight =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", Height[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the Height array pointers
     */

	// HDF Example Method
	free(Height[0]);
	free(Height);

	// Test Method 1
	//for(i = 0; i < dimSize[0]; i++)
		//free((void *)Height[i]);
	//free((void *)Height);

	// Test Method 2
	//free((void *)Height[0]);
	//free((void *)Height);

    /*
	 * Close and release Height dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose Height dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close Height dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SatelliteRange dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	strcat(dsetName,"SatelliteRange");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SatelliteRange dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SatelliteRange dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SatelliteRange dataset : %d\n",rank);
	printf("Dimension sizes of SatelliteRange dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SatelliteRange = (float **) malloc(dimSize[0] * sizeof(float *));
	SatelliteRange[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SatelliteRange[i] = SatelliteRange[0] + i * dimSize[1];

	// Read the SatelliteRange dataset into the SatelliteRange array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SatelliteRange[0]);        // Pointer to buffer receiving data

	printf("\nSatelliteRange read status = %d\n",status);


	printf("\nSatelliteRange =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %11.6f", SatelliteRange[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SatelliteRange array pointers
     */

	// HDF Example Method
	free(SatelliteRange[0]);
	free(SatelliteRange);

    /*
	 * Close and release SatelliteRange dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SatelliteRange dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SatelliteRange dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SCPosition dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"SpacecraftPosition");*/
	strcat(dsetName,"SCPosition");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SCPosition dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SCPosition dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SCPosition dataset : %d\n",rank);
	printf("Dimension sizes of SCPosition dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SCPosition = (float **) malloc(dimSize[0] * sizeof(float *));
	SCPosition[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SCPosition[i] = SCPosition[0] + i * dimSize[1];

	// Read the SCPosition dataset into the SCPosition array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SCPosition[0]);        // Pointer to buffer receiving data

	printf("\nSCPosition read status = %d\n",status);


	printf("\nSCPosition =\n");
	for (i=0; i<dimSize[0]; i++) {
		printf (" [ ");
		for (j=0; j<dimSize[1]; j++){
			printf (" %11.6f", SCPosition[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SCPosition array pointers
     */

	// HDF Example Method
	free(SCPosition[0]);
	free(SCPosition);

    /*
	 * Close and release SCPosition dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SCPosition dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SCPosition dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SCVelocity dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"SpacecraftVelocity");*/
	strcat(dsetName,"SCVelocity");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SCVelocity dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SCVelocity dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SCVelocity dataset : %d\n",rank);
	printf("Dimension sizes of SCVelocity dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SCVelocity = (float **) malloc(dimSize[0] * sizeof(float *));
	SCVelocity[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SCVelocity[i] = SCVelocity[0] + i * dimSize[1];

	// Read the SCVelocity dataset into the SCVelocity array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SCVelocity[0]);        // Pointer to buffer receiving data

	printf("\nSCVelocity read status = %d\n",status);


	printf("\nSCVelocity =\n");
	for (i=0; i<dimSize[0]; i++) {
		printf (" [ ");
		for (j=0; j<dimSize[1]; j++){
			printf (" %11.6f", SCVelocity[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SCVelocity array pointers
     */

	// HDF Example Method
	free(SCVelocity[0]);
	free(SCVelocity);

    /*
	 * Close and release SCVelocity dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SCVelocity dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SCVelocity dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /***********************************************
	 *  Read in the SCAttitude dataset  *
     ***********************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"SpacecraftVelocity");*/
	strcat(dsetName,"SCAttitude");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SCAttitude dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SCAttitude dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SCAttitude dataset : %d\n",rank);
	printf("Dimension sizes of SCAttitude dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float **SCAttitude = (float **) malloc(dimSize[0] * sizeof(float *));
	SCAttitude[0] = (float *) malloc(dimSize[0] * dimSize[1] * sizeof(float));
	for (i=1; i<dimSize[0]; i++)
		SCAttitude[i] = SCAttitude[0] + i * dimSize[1];

	// Read the SCAttitude dataset into the SCAttitude array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SCAttitude[0]);        // Pointer to buffer receiving data

	printf("\nSCAttitude read status = %d\n",status);

	printf("\nSCAttitude =\n");
	for (i=0; i<dimSize[0]; i++) {
		printf (" [ ");
		for (j=0; j<dimSize[1]; j++){
			printf (" %11.6f", SCAttitude[i][j]);
		}
		printf (" ]\n");
	}

    /*
	 * Free the SCAttitude array pointers
     */

	// HDF Example Method
	free(SCAttitude[0]);
	free(SCAttitude);

    /*
	 * Close and release SCAttitude dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SCAttitude dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SCAttitude dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the SCSolarAzimuthAngle dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"SpacecraftVelocity");*/
	strcat(dsetName,"SCSolarAzimuthAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SCSolarAzimuthAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SCSolarAzimuthAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SCSolarAzimuthAngle dataset : %d\n",rank);
	printf("Dimension sizes of SCSolarAzimuthAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float *SCSolarAzimuthAngle = (float *) malloc(dimSize[0] * sizeof(float ));

	// Read the SCSolarAzimuthAngle dataset into the SCSolarAzimuthAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SCSolarAzimuthAngle);        // Pointer to buffer receiving data

	printf("\nSCSolarAzimuthAngle read status = %d\n",status);

	printf("\nSCSolarAzimuthAngle =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %11.6f", SCSolarAzimuthAngle[j]);
	}

    /*
	 * Free the SCSolarAzimuthAngle array pointers
     */

	// HDF Example Method
	free(SCSolarAzimuthAngle);

    /*
	 * Close and release SCSolarAzimuthAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SCSolarAzimuthAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SCSolarAzimuthAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");


    /*****************************************
	 *  Read in the SCSolarZenithAngle dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"SpacecraftVelocity");*/
	strcat(dsetName,"SCSolarZenithAngle");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the SCSolarZenithAngle dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the SCSolarZenithAngle dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of SCSolarZenithAngle dataset : %d\n",rank);
	printf("Dimension sizes of SCSolarZenithAngle dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	float *SCSolarZenithAngle = (float *) malloc(dimSize[0] * sizeof(float ));

	// Read the SCSolarZenithAngle dataset into the SCSolarZenithAngle array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_FLOAT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  SCSolarZenithAngle);        // Pointer to buffer receiving data

	printf("\nSCSolarZenithAngle read status = %d\n",status);

	printf("\nSCSolarZenithAngle =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %11.6f", SCSolarZenithAngle[j]);
	}

    /*
	 * Free the SCSolarZenithAngle array pointers
     */

	// HDF Example Method
	free(SCSolarZenithAngle);

    /*
	 * Close and release SCSolarZenithAngle dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose SCSolarZenithAngle dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close SCSolarZenithAngle dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF1_SCAN_VIIRSSDRGEO dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"QF1_VIIRSIMGGEO");*/
	strcat(dsetName,"QF1_SCAN_VIIRSSDRGEO");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF1_SCAN_VIIRSSDRGEO dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF1_SCAN_VIIRSSDRGEO dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF1_SCAN_VIIRSSDRGEO dataset : %d\n",rank);
	printf("Dimension sizes of QF1_SCAN_VIIRSSDRGEO dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	int *QF1_SCAN_VIIRSSDRGEO = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the QF1_SCAN_VIIRSSDRGEO dataset into the QF1_SCAN_VIIRSSDRGEO array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF1_SCAN_VIIRSSDRGEO);        // Pointer to buffer receiving data

	printf("\nQF1_SCAN_VIIRSSDRGEO read status = %d\n",status);

	printf("\nQF1_SCAN_VIIRSSDRGEO =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %4d", QF1_SCAN_VIIRSSDRGEO[j]);
	}
	printf (" ]\n");

    /*
	 * Free the QF1_SCAN_VIIRSSDRGEO array pointers
     */

	// HDF Example Method
	free(QF1_SCAN_VIIRSSDRGEO);

    /*
	 * Close and release QF1_SCAN_VIIRSSDRGEO dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF1_SCAN_VIIRSSDRGEO dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF1_SCAN_VIIRSSDRGEO dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the QF2_VIIRSSDRGEO dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"QF2_VIIRSIMGGEO");*/
	strcat(dsetName,"QF2_VIIRSSDRGEO");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the QF2_VIIRSSDRGEO dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the QF2_VIIRSSDRGEO dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of QF2_VIIRSSDRGEO dataset : %d\n",rank);
	printf("Dimension sizes of QF2_VIIRSSDRGEO dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	// HDF5 example method
	int **QF2_VIIRSSDRGEO = (int **) malloc(dimSize[0] * sizeof(int *));
	QF2_VIIRSSDRGEO[0] = (int *) malloc(dimSize[0] * dimSize[1] * sizeof(int));
	for (i=1; i<dimSize[0]; i++)
		QF2_VIIRSSDRGEO[i] = QF2_VIIRSSDRGEO[0] + i * dimSize[1];

	// Read the QF2_VIIRSSDRGEO dataset into the QF2_VIIRSSDRGEO array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  QF2_VIIRSSDRGEO[0]);        // Pointer to buffer receiving data

	printf("\nQF2_VIIRSSDRGEO read status = %d\n",status);


	printf("\nQF2_VIIRSSDRGEO =\n");
	for (i=0; i<10; i++) {
		printf (" [ ");
		for (j=0; j<10; j++){
			printf (" %4d", QF2_VIIRSSDRGEO[i][j]);
			//printf (" %4d", *(QF2_VIIRSSDRGEO[i] + j));
		}
		printf (" ]\n");
	}

    /*
	 * Free the QF2_VIIRSSDRGEO array pointers
     */

	// HDF Example Method
	free(QF2_VIIRSSDRGEO[0]);
	free(QF2_VIIRSSDRGEO);

    /*
	 * Close and release QF2_VIIRSSDRGEO dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose QF2_VIIRSSDRGEO dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close QF2_VIIRSSDRGEO dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************
	 *  Read in the PadByte1 dataset  *
     *****************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"Pad");*/
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

    /*
	 * Allocate memory for our array
     */

	int *PadByte1 = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the PadByte1 dataset into the PadByte1 array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
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

    /*
	 * Free the PadByte1 array pointers
     */

	// HDF Example Method
	free(PadByte1);

    /*
	 * Close and release PadByte1 dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose PadByte1 dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close PadByte1 dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the ModeScan dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"ScanMode");*/
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

	int *ModeScan = (int *) malloc(dimSize[0] * sizeof(int));

	// Read the ModeScan dataset into the ModeScan array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
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
	 *  Read in the ScanStartTime dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"ScanStartTime");*/
	strcat(dsetName,"StartTime");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the StartTime dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the StartTime dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of StartTime dataset : %d\n",rank);
	printf("Dimension sizes of StartTime dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	long *StartTime = (long *) malloc(dimSize[0] * sizeof(long));

	// Read the StartTime dataset into the StartTime array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_LONG,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  StartTime);        // Pointer to buffer receiving data

	printf("\nStartTime read status = %d\n",status);

	printf("\nStartTime =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %ld", StartTime[j]);
	}
	printf (" ]\n");

    /*
	 * Free the StartTime array pointers
     */

	// HDF Example Method
	free(StartTime);

    /*
	 * Close and release StartTime dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose StartTime dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close StartTime dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************************
	 *  Read in the MidTime dataset  *
     *****************************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"ScanMidTime");*/
	strcat(dsetName,"MidTime");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the MidTime dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the MidTime dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of MidTime dataset : %d\n",rank);
	printf("Dimension sizes of MidTime dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	long *MidTime = (long *) malloc(dimSize[0] * sizeof(long));

	// Read the MidTime dataset into the MidTime array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_LONG,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  MidTime);        // Pointer to buffer receiving data

	printf("\nMidTime read status = %d\n",status);

	printf("\nMidTime =\n");
	printf (" [ ");
	for (j=0; j<dimSize[0]; j++){
		printf (" %ld", MidTime[j]);
	}
	printf (" ]\n");

    /*
	 * Free the MidTime array pointers
     */

	// HDF Example Method
	free(MidTime);

    /*
	 * Close and release MidTime dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose MidTime dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close MidTime dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************
	 *  Read in the NumberOfScans dataset  *
     *****************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"ActualScans");*/
	strcat(dsetName,"NumberOfScans");
	printf("\nDataset name is : %s\n",dsetName);

	// Get the dataset ID for the NumberOfScans dataset
	dsetID = H5Dopen (fileID, dsetName, H5P_DEFAULT);

    // Get dataspace and allocate memory for read buffer.  This is a
    // two dimensional dataset so the dynamic allocation must be done
    // in steps.
	dspaceID = H5Dget_space(dsetID);

	// Get the number of dimensions, dimension sizes and maximum dimension
	// sizes for the NumberOfScans dataset (through the associated dataspace)
	rank = H5Sget_simple_extent_dims(dspaceID, dimSize, NULL);

	printf("Rank of NumberOfScans dataset : %d\n",rank);
	printf("Dimension sizes of NumberOfScans dataset : ");
	for (i=0;i<rank;i++) printf("%llu\t",dimSize[i]);

    /*
	 * Allocate memory for our array
     */

	int NumberOfScans;

	// Read the NumberOfScans dataset into the NumberOfScans array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  &NumberOfScans);        // Pointer to buffer receiving data

	printf("\nNumberOfScans read status = %d\n",status);

	printf("\nNumberOfScans = ");
	printf (" %4d", NumberOfScans);

    /*
	 * Close and release NumberOfScans dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose NumberOfScans dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close NumberOfScans dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /*****************************
	 *  Read in the ModeGran dataset  *
     *****************************/

	strcpy(dsetName,IMGGEOGRP);
	/*strcat(dsetName,"ActualScans");*/
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

    /*
	 * Allocate memory for our array
     */

	int ModeGran;

	// Read the ModeGran dataset into the ModeGran array
	status = H5Dread (dsetID,              // dataset ID
					  H5T_NATIVE_INT,    // ident of memory datatype
					  H5S_ALL,             // ident of memory dataspace
					  H5S_ALL,             // ident of dataset's dataspace in file
					  H5P_DEFAULT,         // File access properties
					  &ModeGran);        // Pointer to buffer receiving data

	printf("\nModeGran read status = %d\n",status);

	printf("\nModeGran = ");
	printf (" %4d", ModeGran);

    /*
	 * Close and release ModeGran dataset and dataspace
     */
	status = H5Dclose (dsetID);
	printf("\n\nClose ModeGran dataset status = %d\n",status);
	status = H5Sclose (dspaceID);
	printf("Close ModeGran dataspace status = %d\n",status);

	printf ("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

    /****************************
	 *  Clean up for this file  *
     ****************************/

	// Close and release file.
	status = H5Fclose (fileID);


	return 0;
}
