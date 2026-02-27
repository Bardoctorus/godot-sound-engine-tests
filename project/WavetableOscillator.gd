class_name WavetableOscillator

var waveTable
var sampleRate
var index: float
var increment: float
var frequency
var isPlaying: bool

func _init (_waveTable, _sampleRate, _frequency):
	waveTable = _waveTable
	sampleRate = _sampleRate
	setFrequency(_frequency)
	isPlaying = false
	
func getSample() -> float:
	if isPlaying:
		index = fmod(index, waveTable.size() as float)
		var sample: float = interpolateLinearly()
		index += increment
		return sample
	else:
		return 0
	
func setFrequency(_frequency: float):
	frequency = _frequency
	increment = frequency * (waveTable.size() as float / sampleRate as float)
	
func start():
	setFrequency(frequency)
	isPlaying = true
	
	
func update(_frequency):
	setFrequency(_frequency)


	
func stop():
	isPlaying = false
	index = 0
	increment = 0
	


func interpolateLinearly() -> float:
	var truncatedIndex: int = floor(index)
	var nextIndex: int = ceil(index) as int % waveTable.size()
	var nextIndexWeight: float = index - truncatedIndex as float
	return waveTable[nextIndex] * nextIndexWeight + (1 - nextIndexWeight) * waveTable[truncatedIndex]
	

	
