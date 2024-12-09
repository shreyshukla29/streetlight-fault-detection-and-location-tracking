
* * * * *

**Centralized Monitoring System for Street Light Fault Detection**
==================================================================

**Description**
---------------

This project implements a centralized monitoring system for detecting faults in streetlights using ESP32, IR sensors, LDRs, GPS, and Firebase Realtime Database. The system identifies streetlights with faults, tracks their location, and updates their status in real time for efficient management and repair.

Key Features:

-   **Real-time Monitoring:** Continuously monitors streetlight statuses using IR sensors and LDRs.
-   **Fault Detection:** Detects faults and identifies whether the lights are functional.
-   **Location Tracking:** Uses GPS to track the exact location of faulty streetlights.
-   **Centralized Database:** Updates statuses and locations in Firebase Realtime Database.

* * * * *

**Technologies Used**
---------------------

-   **Hardware**: ESP32, IR sensors, LDRs, GPS module.
-   **Software**: Arduino IDE, Firebase Realtime Database.
-   **Programming Language**: C++ (Arduino framework).

* * * * *

**Features**
------------

-   Detects streetlight faults using LDR and IR sensors.
-   Sends real-time updates to Firebase.
-   Tracks the latitude and longitude of faulty streetlights.
-   Maintains statuses (`ON`/`OFF`) for better visibility and management.

* * * * *

**System Workflow**
-------------------

Here's how the system works:

1.  **Fault Detection**:

    -   LDR sensors monitor light intensity to determine if the streetlight is working.
    -   IR sensors detect motion to ensure activity monitoring.
    -   Faults are identified when either sensor returns abnormal values.
2.  **Status Update**:

    -   The ESP32 sends the streetlight's status (ON/OFF) to Firebase.
    -   Statuses are stored in paths like `ledStatus/ledX` (where X is the streetlight ID).
3.  **Location Tracking**:

    -   GPS data is collected for faulty streetlights.
    -   Locations are stored in Firebase paths like `faultledlocation/ledLatitudeX` and `faultledlocation/ledLongitudeX`.
4.  **Real-time Control**:

    -   The database allows for programmatic control of streetlights based on collected data.

* * * * *

**Hardware Connections**
------------------------

| **Component** | **Pin Connection** |
| --- | --- |
| IR Sensor 1 | Pin 12 |
| IR Sensor 2 | Pin 14 |
| LDR Sensor | Pin 32 |
| LED 1 | Pin 0 |
| LED 2 | Pin 4 |
| LED 3 | Pin 16 |
| LED 4 | Pin 17 |

* * * * *

**Setup Instructions**
----------------------

### **1\. Clone the Repository**

    
     git clone https://github.com/YourUsername/StreetLightMonitoringSystem.git
     cd StreetLightMonitoringSystem

### **2\. Hardware Setup**

-   Connect ESP32 with the sensors and LEDs as per the pin configuration.

### **3\. Install Dependencies**

-   Open Arduino IDE and install the following libraries:
    -   **Firebase ESP Client**: For Firebase integration.
    -   **TinyGPS++**: For GPS data parsing.
    -   **WiFi**: For connecting to the internet.

#### Installing Libraries

1.  Go to **Sketch → Include Library → Manage Libraries**.
2.  Search for each library (e.g., `Firebase ESP Client`) and install it.

* * * * *

### **4\. Firebase Integration**

#### **Step 1: Set Up Firebase**

1.  Go to Firebase Console and create a project.
2.  Navigate to the **Realtime Database** section and enable it.
3.  Note down the database URL (e.g., `https://<your-project>.firebaseio.com`).
4.  In the **Project Settings**, generate an **API Key**.

#### **Step 2: Configure Firebase in Code**

1.  Replace the placeholders in the code:

        #define WIFI_SSID "Your_SSID"
        #define WIFI_PASSWORD "Your_Password"
        #define API_KEY "Your_Firebase_API_Key"
        #define DATABASE_URL "https://<your-project>.firebaseio.com"

2.  Upload the updated code to ESP32.

* * * * *

### **5\. Run the Project**

-   Open the serial monitor in Arduino IDE to view logs.
-   Check the Firebase Realtime Database for real-time updates on streetlight statuses and locations.

* * * * *

**Code Structure**
------------------


    StreetLightMonitoringSystem/
    ├── main.ino              # Main Arduino sketch
    ├── libraries/            # Required libraries
    ├── README.md             # Project documentation
    └── assets/               # Images/diagrams 

* * * * *

**Example Firebase Data Paths**
-------------------------------

Here's how data will be structured in Firebase:

-   **LED Status**:

        ledStatus/
         ├── led1: "ON"
         ├── led2: "OFF"`

-   **Faulty LED Locations**:


        faultledlocation/
        ├── ledLatitude1: 28.6139
        ├── ledLongitude1: 77.2090

* * * * *


**Usage**
---------

-   Monitor the serial output for real-time updates.
-   View the status and location of streetlights in the Firebase Realtime Database.

* * * * *

**Screenshots/Diagrams**
------------------------

### **1\. App Image**

![App Image](https://github.com/user-attachments/assets/d3dff2d2-9b3d-4dcd-9c25-a0bee0c8e9ee)

* * * * *

### **2\. Arduino Terminal Image**

![Arduino Terminal Image](https://github.com/user-attachments/assets/d591b5b2-79b0-4f0a-837f-29bf4b6ff2da)

* * * * *

### **3\. Firebase Database Image**

![Firebase Database Image](https://github.com/user-attachments/assets/6833e50a-c4cd-4a06-bfbe-af3dd0f3b499)

------------------------

**License**
-----------

This project is licensed under the MIT License.

* * * * *

**Contact**
-----------

-   **GitHub**: [shreyshukla29](https://github.com/shreyshukla29)
-   **Email**: shreyshukla101217@gmail.com

* * * * *
