# ClientTFTP_Mathlouthi_TahaYassine

**Objectives**: Create a TFTP client, using RFCs and wireshark captures.

We're going to create a client program capable of exchanging files using the
TFTP* (Trivial File Transfer Protocol). To do this, we'll need to rely on RFCs and wireshark captures.

_*This TFTP protocol is used for OS installation over the network (PXE protocol)
diskless node), for updating firmware on network devices (PXE), and for the
network equipment (routers, IoT...)_

____________________________________________________________________________________________________________________________________________________________________________

We'll be implementing new functionalities as we go along._

**STEP 1**: Use the arguments passed on the command line of the gettftp and
puttftp programs to obtain request information (server and file)

**STEP 2**: 