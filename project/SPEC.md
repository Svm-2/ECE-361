# EV Charging Station — SPEC

| State | Meaning |
|---|---|
| IDLE | no car connected (initial state) |
| HANDSHAKE | car connected, negotiating |
| CHARGING | full power |
| THROTTLED | half power because of heat |
| FAULT | charging stopped until unplugged |

## Events

### Switches
| Bit | Switch | Kind | Meaning |
|---|---|---|---|
| 0 | PLUGGED | level | cable connected to a car |
| 1 | CAR_READY | level | the car accepted the charge |
| 2 | START | press | a start command |
| 3 | STOP | press | a stop command |

### LEDs
| Bit | LED | On means |
|---|---|---|
| 0 | CONTACTOR | power contactor closed |
| 1 | THROTTLE | reduced power |
| 2 | FAULT_LAMP | fault |

### Temperature events
- Above 45.0 C: throttle
- At or below 40.0 C: return to full power
- Above 55.0 C: fault