#  Node-RED & Alexa integration Setup
## Features

### **Amazon Alexa Integration** (optional)

It works with any language that is supported by Alexa and can be easily expanded to support more activities or patterns. How you want to call them (Nanoleaf, Nanoleafs, Nano, Triangles) must be set in the setup of the devices.

#### **Commands**:

- Turn on/off
- Control Brightness
- Control Pattern Speed					    
- Set Color
- Set into Rainbow mode					  
- Enable Autoplay and set Duration	
- Activate custom activities		

> *Alexa, turn Nanoleafs **on/off***
> *Alexa, set Nanoleafs 70%*
> Alexa, dim Nanoleafs
> *Alexa, Nanoleaf speed 20%*
> *Alexa, set Nanoleafs pink*
> *Alexa, turn Nanoleaf rainbow on*
> *Alexa, turn Nanoleaf Autoplay on*
> *Alexa, set Nanoleaf Autoplay 40*
>
> Alexa, Nanoleaf Default
> Alexa, Nanoleaf Mode 1
> Alexa, Nanoleaf Mode 2
> Alexa, Nanoleaf Mode 3



### Node-RED GUI

The Node-RED GUI is an addition to the regular UI that is running on the Wemos D1 mini. It allows to create and save custom patterns and also control all regular parameters same as the ESP8266 webserver. It can be accessed by any device.

 ![full](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/full.png?raw=true)



#### Nanoleaf Designer

In the Node-RED GUI you can easily create your nanoleaf setup by using the *Nanoleaf Designer*. It's easy to use and allows almost any design that is possible. But it might have still some minor bugs.

![nanoleaf_designer](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/nanoleaf_designer.png?raw=true)



![nanoleaf_designer_2](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/nanoleaf_designer_2.png?raw=true)



#### Nanoleaf Custom Pattern Designer

With the *Nanoleaf Custom Pattern Designer* you can create custom patterns with effects. Currently the individual leafs can be set to *Static* mode and *Breathe* mode that allows to set a phase shift and lets the leafs breathe. Flow-mode follows in the next update.

![pattern_designer](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/pattern_designer.png?raw=true)



![pattern_designer_2](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/pattern_designer_2.png?raw=true)



![patternlist](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/patternlist.png?raw=true)





## What you will need

- Any device that runs Node-RED, examples would be:
  - (recommended)  [Raspberry Pi](https://www.amazon.de/gp/product/B01CD5VC92?ie=UTF8&tag=surrbradl08-21&camp=1638&linkCode=xm2&creativeASIN=B01CD5VC92)
  - Any Linux machine
  - (instructions are provided for linux) Any Windows machine
- Any Amazon Alexa device for Alexa integration, works on Android and IOS too (**OPTIONAL**)





## Setup

#### 1. Install Node-RED

```bash
bash <(curl -sL https://raw.githubusercontent.com/node-red/raspbian-deb-package/master/resources/update-nodejs-and-nodered)
```



#### 2. Install npm - this might be already installed

```bash
sudo apt-get install nodejs npm -y
```



#### 3. Install dashboard, alexa-home-skill, color-convert, config

```bash
cd $HOME/.node-red
npm install node-red-dashboard
```

- if you get an error try: `npm install --unsafe-perm node-red-dashboard`

```bash
npm install node-red-contrib-alexa-home-skill
npm install node-red-contrib-color-convert
npm install node-red-contrib-config
```



#### 4. Setup a static IP-Address for your Raspberry Pi (optional)

- (recommended) Setup a static ip on your router
- [or on your Raspberry Pi](http://www.circuitbasics.com/how-to-set-up-a-static-ip-on-the-raspberry-pi/)



#### 5. Run Node-RED

To start Node-RED type into the shell:

```bash
sudo node-red-start
```

Connect to the GUI by typing the following line into your browser:

- http://IP-ADDRESS:1880



#### 6. Import the flow

- Click on the 3 dashes in the top right corner → import → clipboard
- Copy the contents of NodeRED_flows.txt into the window and hit import

![import](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/import.png?raw=true)



#### 7. Configure the IP-Address of the Wemos D1 mini

Edit the Nanoleaf-Config node to set the IP-Address.

![config_1](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/config_1.png?raw=true)

![config_2](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/config_2.png?raw=true)


#### 8. Connect to the Dashboard

Connect to the dashboard(website) of Node-RED by typing the following line into your browser:

- http://IP-ADDRESS:1880/ui


## Amazon Alexa setup

The Alexa integration uses the *Node-RED Alexa Home Skill Bridge* to redirect the commands from alexa to Node-RED.



### 1. Create a new Bridge account

Head to https://alexa-node-red.bm.hardill.me.uk/newuser and create a new account.

Afterwards login into your account.



### 2. Create the Devices

You have to create devices that are called by Alexa.

#### 2.1 Main Nanoleaf Device

First create the devices that control a few devices that are used to turn on/off the nanoleafs and controls the brightness. I've called them "Nanoleafs", "Nanoleaf", "Nano" and "Triangles", but a single one would be enough too.

Click the **Add Device** button and choose. Repeat this step for all your names.

![device_1](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/device_1.png?raw=true)

![device_2](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/device_2.png?raw=true)



#### 2.2 Autoplay control Device (optional)

To control the autoplay functionality, create a device with **On, Off, %, +%, -%, LIGHT**.



#### 2.3 Speed control Device (optional) 

To control the speed of the animations,  create a device with **%, +%, -%**.



#### 2.4 Activities (optional)

Now create activities by clicking *Add Device* and selecting **On, Off, ACTIVITY**.

I've created one to set the *Rainbow* pattern, one for my default settings and Nanoleaf Mode 1-3 for some custom settings.

![device_3](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/device_3.png?raw=true)

![device_4](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/device_4.png?raw=true)



### 3. Activating the Alexa skill

Open the app on your phone or head to https://alexa.amazon.de and click on **Skills**.

Search for **Node-RED** and activate the skill. Afterwards you are prompted to login into your account that you have created the devices beforehand.

![1551006980428](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/alexa_skill.png?raw=true)



### 4. Add a new Alexa-Home-Skill configuration

Click on any Alexa node in the flow, and click *Add new alexa-home-configuration*. Afterwards hit the refresh button next to the devices list.

![conf_1](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/conf_1.png?raw=true)





### 5. Select the devices

Click the alexa skill nodes in the flow and select the corresponding devices. **Delete all unused alexa nodes**.

For me, it looked like this:

![device_config](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/NodeRED_UI/device_config.png?raw=true)

### 6. Discover the Smart-Home Devices

Speak to Alexa and say to her: **Alexa, discover devices**. (Just say it in english, it works on every device)

If everything worked correctly she should tell you after around 30 seconds that she has found new devices.