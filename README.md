# Drive-Project

Product Idea:

    Product: Drive (Virtual Storage System) that stores the end-user's data on small IoT components located in smart electrical devices (e.g., water heaters, lighting, etc.), referred to as 
    "minyons".

Advantages:

    File Security: Files are stored on the "minyons" so that if the computer is damaged or stolen, the data will not be lost.

    Disk Space Savings: Less significant, as disk space is not expensive.
    
Installation:

    Client: The client-side is free - self-installation from the internet.

    minyon: The "minyon" side is not free. A license is purchased per unit by the manufacturer of IoT devices.

Functional Requirements (What the product does):

    GUI: A regular Linux directory. No development required.

    Persistency: Basic - as long as the data is stored on the "minyon," if the system crashes and restarts, the data will not be lost.

    Plugin: Support for dynamic version updates on both sides.

Non-Functional Requirements (How the product works):

    RAID01: A type of storage configuration across different disks. This configuration maps logical locations from all disks to specific physical locations. It supports parallelism (spreading read
    and write operations across multiple "minyons" to improve performance - each read/write operation has a non-overlapping offset and size, so they can be performed in parallel) and backup
    (replicating data from one "minyon" to another, so if data is lost in one, it is backed up in the other).

    Error Handling: Verification that read or write operations to the "minyon" were successful.

    Generics: Creating a generic framework. This reduces code duplication and serves as a basic tool for creating various software programs with similar behavior.

    Portability: Portability begins once the TCP message is sent from the NBD. The NBD and the flow preceding it are relevant only for a Linux-based operating system.
