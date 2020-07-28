import pickle

def LoadPickle(filepath):
	print("Loading pickle file: {}".format(filepath))
	fd = open(filepath, 'rb')
	p = pickle.load(fd, encoding='latin1')
	fd.close()
	return p