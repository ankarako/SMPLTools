import pickle

def LoadPickle(filepath):
	print("Loading pickle file: {}".format(filepath))
	fd = open(filepath, 'rb')
	p = pickle.load(fd, encoding='latin1')
	fd.close()
	# convert to primitive python types
	result = {
		"Faces": p['f'].tolist(),
		"Vertices": p['v_template'].tolist(),
		"JointPositions": p['J'].tolist()

	}
	print(result)
	return result