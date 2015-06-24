# PRUTOOL

The PRUTOOL can control the PRUs via the command line.

## How to use it

- Halt PRU0 `prutool h 0`
- Halt PRU1 `prutool h 1`

- Start PRU0 `prutool s 0`
- Start PRU1 `prutool s 1`

- Load file in PRU0 IRAM `prutool i 0 iramfilename`
- Load file in PRU1 IRAM `prutool i 1 iramfilename`

- Load file in PRU0 DRAM `prutool d 0 dramfilename`
- Load file in PRU1 DRAM `prutool d 1 dramfilename`

- Load file in PRU0 IRAM and DRAM `prutool l 0 iramfilename dramfilename`
- Load file in PRU1 IRAM and DRAM `prutool l 1 iramfilename dramfilename`

## Example

Make sure you have installed the TI PRU Code Generation Tools. To install the tools use `sudo apt-get install ti-pru-cgt-installer` 

- Change to the example folder `cd example`
- Compile and build nessecary file `make`
- Change back to prutool folder `cd ..`
- Create prutool once `make`
- Halt PRU1 `prutool h 1`
- Load IRAM and DRAM into PRU1 `prutool l 1 example/text.bin example/data.bin`
- Start program in PRU1 `prutool s 1`
