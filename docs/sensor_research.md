# Sensor Research

## Top 3 Air Quality Monitors

### Air Quality Egg
Links:
* https://airqualityegg.com/shop 

Notes:
* Temperature/humidity/pressure
* Can customize for other sensors, such as VOCs or CO
* API: https://airqualityegg.wickeddevice.com/api-docs/ 
* Data is public unless you have a corporate subscription
* Price: $360 if we add PM, VOCs, and CO2

### IQAir AirVisual Pro
Links:
* https://www.iqair.com/us/air-quality-monitors/airvisual-series 

Notes:
* PM2.5/CO2/temperature/humidity
* No VOCs
* Wifi connection
* Smart integration (IFTTT, API)
* Price: $379.00CAD/$269.00USD

### Purple Air
Links:
* https://www2.purpleair.com/collections/air-quality-sensors/products/purpleair-pa-i-indoor
* https://www2.purpleair.com/community/faq 

Notes:
* Detects PM2.5, pressure, temperature, and humidity
* No VOCs
* Wifi connection
* Access data directly or use ThingSpeak API
* Price: $199

## Premade Sensors

### Temtop M10i Wifi
Links:
* https://temtopus.com/collections/wifi-air-quality-monitor/products/temtop-m10i-wireless-air-quality-monitor-for-pm2-5-hcho-tvoc-aqi-professional-electrochemical-sensor-detector-real-time-display 
* https://jorsh.xyz/blog/20200526-temtop-M10i-API/ 

Notes:
* PM2.5/formaldehyde/TVOC
* Wifi connection
* No API (but see the 2nd link)
* Price: $175.99 (USD?)

### Airbeam
Links:
* https://www.habitatmap.org/airbeam/how-it-works
* https://scistarter.org/aircasting 
* https://www.valarm.net/blog/airbeam-aircasting-air-quality-sensors-with-valarm-tools-cloud/ 

Notes:
* PM2.5/temperature/humidity
* Powered by Arduino Leonardo
* Price: $249.00USD
* No wifi

### HibouAir
Links:
* https://smartsensordevices.com/hibouair-particle-and-co2-sensor/
* https://www.smartsensordevices.com/wp-content/uploads/2020/03/* hibou-Air-Quality-sensor-system-Blad-R05.pdf

Notes:
* Can either get CO2/VOCs/humidity/temperature/atm pressure/light or PM2.5/VOCs/humidity/temperature/pressure/light
* Comes with iot cloud subscription (is this required?)
* Need a plan for API access, rather than just a single device? https://smartsensordevices.com/services/indoor-air-quality-monitoring/
* From Sweden: probably can't get one very quickly, shipping is $40
* Price: $235.00USD for PM2.5, $255.00USD for CO2

### Atmotube PRO
Links:
* https://atmotube.com/products/atmotube-pro
* https://help.atmotube.com/technical/12-atmotube-api/ 

Notes:
* Wearable/portable monitor
* PM2.5/VOCs/temperature/humidity/pressure
* Does NOT measure CO2
* Bluetooth API
* Cloud API in beta: can contact for early access
* Price: $259.00 (USD?)

### Flow 2
Links:
* https://plumelabs.com/en/flow/ 
* https://plumelabs.com/en/sensor-fleets/ 

Notes:
* PM2.5/NO2/VOCs
* Battery lasts 24-72 hrs
* Portable 
* API access is $3 per device per month
* Price: $199.00CAD

### Kaiterra
Links:
* https://restechtoday.com/kaiterra-laser-egg-chemical/
* https://www.bedbreezzz.com/ 

Notes:
* Uses laser instead of IR for PM2.5 detection (more accurate)
* Can get either CO2/PM2.5/temperature/humidity or PM2.5/TVOC/temperature/humidity
* Makes a loud humming noise
* Price: $199.00USD/$251.85CAD per unit

### AirThings
Links:
* https://shop.airthings.com/CA_HBS/hbs-intro-kit-usca.html?_gl=1*of0kvm*_ga*MTM4NDQwMzc1OS4xNjM1NDQxMzc5*_ga_88NZ2TFTKX*MTYzNTQ0MTM3OS4xLjEuMTYzNTQ0MTYzMS41OA

Notes:
* Radon/TVOC/CO2/temperature/humidity/pressure/light
* Units communicate with hub via Bluetooth, hub has wifi connection
* Need business pack for access to API: 5 units and a hub
* Price: $2700.00 for business pack

### Halo
Links:
* https://ipvideocorp.com/halo/
* https://www.cdw.com/product/halo-iot-smart-sensor/5850652

Notes:
* Detects particulates, VOCs, CO2, temperature, humidity, pressure, light, and more
* Also detects abnormal noise levels
* Price: $1295.00

### uHoo
Links:
* https://getuhoo.com/
* https://getuhoo.com/business 
* https://www.trutechtools.com/uHoo-Enterprise-Account

Notes:
* Detects PM2.5, CO2, VOCs, pressure, humidity, temperature
* Need business version for API

### HoneyWell Transmission Risk Air Monitor (HTRAM)
Links:
* https://www.schoolspecialty.com/honeywell-transmission-risk-air-monitor-2088969
* https://sps.honeywell.com/us/en/products/safety/gas-and-flame-detection/portables/honeywell-transmission-risk-air-monitor
* https://sps.honeywell.com/us/en/campaigns/safety/transmission-risk-air-monitor?utm_source=google_search_ad&utm_medium=cpc&utm_campaign=htram_launch-21_10-usc-en&utm_content=paid_ad&s_kwcid=AL!7892!3!553324875517!p!!g!!air%20monitor&gclid=CjwKCAjwiY6MBhBqEiwARFSCPsp_svURw1FRoOIPNpEniFkay1j_8HfAPXV1z5TFjcLWTKcIdQnrAxoCt1EQAvD_BwE
* https://en.safetygas.com/capteur-co2-covid-htram

Notes:
* CO2/temperature/humidity
* Non-dispersive IR
* 10hr battery life
* Portable
* Does the dev kit work for this? https://sps.honeywell.com/ca/en/software/productivity/development-tools/guided-work-tools 
* Price: $284.96

### HoneyWell IOT Sensors
* https://sps.honeywell.com/us/en/products/sensing-and-iot/sensors/gas-sensors/aq3-series
* https://sps.honeywell.com/us/en/products/sensing-and-iot/sensors/particulate-matter-sensors/hpm-series 


## RPi/Arduino Equipment

### DIY Tutorial
Links:
* https://www.airgradient.com/diy/

Notes:
* Exact parts for this tutorial are significantly more expensive on Amazon
* If ordered from the recommended website, parts wouldn’t come in until January

### CO2/TVOC Sensor
Links:
* https://www.amazon.ca/KEYESTUDIO-Dioxide-Detector-Quality-Temperature/dp/B086HCSM6N/ref=sr_1_5?crid=2C0UL1NSJ2TX4&keywords=Co2+sensor&qid=1636223087&refinements=p_85%3A5690392011&rnid=5690384011&rps=1&sprefix=co2+sensor%2Caps%2C120&sr=8-5
* https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor

Notes:
* Digital sensor
* Price: $19.89CAD

### PM2.5 Sensor
Links:
* https://www.amazon.ca/flashtree-Digital-Particle-Concentration-Breakout/dp/B08JM7CL29/ref=pd_sbs_1/131-2186359-6736410?pd_rd_w=8VmCk&pf_rd_p=01fdeee8-dd76-431b-910b-f00bfed49bd2&pf_rd_r=HAHKDHKB5QV5ET0E6BRK&pd_rd_r=ef861dc0-faa2-4431-bae9-440364aa8a90&pd_rd_wg=qoucW&pd_rd_i=B08JM7CL29&psc=1

Notes:
* Digital sensor
* Price: $29.99CAD
