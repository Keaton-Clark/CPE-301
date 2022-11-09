all:
	sudo arduino-cli compile --fqbn arduino:avr:mega sketch
install: all
	sudo arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega sketch
	
