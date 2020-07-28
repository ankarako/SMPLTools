import _pickle as pickle

def LoadPickle(filepath):
	print("Loading pickle file: {}".format(filepath))
	fd = open(filepath, 'rb')
	p = pickle.load(fd, fix_imports=True, encoding='latin1')
	fd.close()
	# convert to primitive python types
	result = {
		"Faces": p['f'].tolist(),
		"Vertices": p['v_template'].tolist(),
		"JointNames": p['joint2num'].tolist()
	}
	print(result)
	return result

###############
# Test Loading
###############
if __name__=="__main__":
	filepath = r"E:\_dev\_PhD\SMPL\SMPLX\models_smplx_v1_0\models\smplx\SMPLX_FEMALE.pkl"
	res = LoadPickle(filepath)
