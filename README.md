# ClientTFTP_Mathlouthi_TahaYassine

**Objectives**: Create a TFTP client, using RFCs and wireshark captures.

We're going to create a client program capable of exchanging files using the
TFTP* (Trivial File Transfer Protocol). To do this, we'll need to rely on RFCs and wireshark captures.

_*This TFTP protocol is used for OS installation over the network (PXE protocol)
diskless node), for updating firmware on network devices (PXE), and for the
network equipment (routers, IoT...)_

____________________________________________________________________________________________________________________________________________________________________________

We'll be implementing new functionalities as we go along._Starting from Question 4, we choose to implement everything within a common `main` function to avoid duplicating similar lines of code.

**STEP 1**: Use the arguments passed on the command line of the gettftp and
puttftp programs to obtain request information (server and file)

**STEP 2**: Allocate a connection socket to the server.

**STEP 3**: For the gettftp function:
a) Construct a well-formed Read Request (RRQ) and send it to the server.
b) Receive a file consisting of a single Data (DAT) packet and its acknowledgment (ACK).
c) Receive a file consisting of multiple Data (DAT) packets and their respective acknowledgments (ACK).

**STEP 4**: For the puttftp function:
a) Construct a well-formed Write Request (WRQ) and send it to the server.
b) Send a file consisting of a single Data (DAT) packet and receive its acknowledgment (ACK).
c) Send a file consisting of multiple Data (DAT) packets and receive their respective acknowledgments (ACK).

**STEP 5**: Utilize the blocksize option.

**STEP 6**:  Search for the optimal blocksize.

**STEP 7**: Manage packet losses (and consequently acknowledgments) and error packets (ERR)