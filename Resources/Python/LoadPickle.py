import _pickle as pickle

def LoadPickle(filepath):
	print("Loading pickle file: {}".format(filepath))
	fd = open(filepath, 'rb')
	p = pickle.load(fd, fix_imports=True, encoding='latin1')
	fd.close()

	# convert dynamic_lmk_bary_coords arrays to lists
	for i in range(len(p['dynamic_lmk_bary_coords'])):
		p['dynamic_lmk_bary_coords'][i] = p['dynamic_lmk_bary_coords'][i].tolist()

	# convert to "primitive" python types
	result = {
		"Faces": p['f'].tolist(),
		"Vertices": p['v_template'].tolist(),
		"JointNames": p['joint2num'].tolist(),
		"PartNames": p['part2num'].tolist(),
		"SkinningWeights" : p['weights'].tolist(),
		"ShapeDirections" : p['shapedirs'].tolist(),
		"PoseDirections": p['posedirs'].tolist(),
		"JRegressor": p['J_regressor'].tolist(),
		"HandsComponentsL": p['hands_componentsl'].tolist(),
		"HandsComponentsR": p['hands_componentsr'].tolist(),
		"HandsCoefficientsL": p['hands_coeffsl'].tolist(),
		"HandsCoefficientsR": p['hands_coeffsr'].tolist(),
		"DynamicLMKFacesIdx": p['dynamic_lmk_faces_idx'].tolist(),
		"DynamicLMKBaryCoords": p['dynamic_lmk_bary_coords'],
		"HandsMeanL": p['hands_meanl'].tolist(),
		"HandsMeanR": p['hands_meanr'].tolist(),
		"LMKFacesIdx": p['lmk_faces_idx'].tolist(),
		"LMKBaryCoords": p['lmk_bary_coords'].tolist(),
	}
	return result

###############
# Test Loading
###############
if __name__=="__main__":
	filepath = r"D:\_dev\_PhD\Resources\SMPLX\models\models_smplx_v1_0\models\smplx\SMPLX_FEMALE.pkl"
	res = LoadPickle(filepath)
