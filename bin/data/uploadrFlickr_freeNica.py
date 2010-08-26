

api_secret="e9498236cef03906"
api_key="da9c1c37763afd431577e542cef2e5ab"
api_token ="72157624343999457-340984552161eee1"

# in python console (secret + key)
#flickr=flickrapi.FlickrAPI(api_key,api_secret)
#(token,frob)= flickr.get_token_part_one(perms='write')
#flickr.get_token_part_two((token, frob))


import flickrapi
import sys
import getopt

def main():
    # parse command line options
    imgPath = sys.argv[1]
    imgTitle = sys.argv[2]
    flickr = flickrapi.FlickrAPI(api_key, api_secret, token=api_token)
    flickr.upload(filename=imgPath, tags='free.nica ars-electronica', title=imgTitle, set='72157624351617795')


if __name__ == "__main__":
    main()
