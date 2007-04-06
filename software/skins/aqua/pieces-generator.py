for i in range(1,13):
	print '\t<!-- About the piece ' + str(i)+ ' -->'
	print '\t<section name = "piece_' + str(i) + '">'
	print ""
	print "\t\t<!-- Normal sprite, which you see the most of the time -->"
	print "\t\t<sprite name = \"normal\">"
	print "\t\t\t<image file = \"piece"+str(i)+"/normal.png\" />"
	print	'\t\t</sprite>'
	print ''
	print '\t\t<!-- Appearing sprite, when you create one -->'
	print '\t\t<sprite name = "appear">'
	print '\t\t\t<image file="piece'+str(i)+'/appear.png">'
	print '\t\t\t\t<grid pos="0,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<image file="piece'+str(i)+'/appear.png">'
	print '\t\t\t\t<grid pos="50,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<image file="piece'+str(i)+'/appear.png">'
	print '\t\t\t\t<grid pos="100,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<animation speed="50" />'
	print '\t\t</sprite>'
	print ''
	print '\t\t<!-- Disappearing sprite, when you brokes three or more -->'
	print '\t\t<sprite name = "disappear">'
	print '\t\t\t<image file="piece'+str(i)+'/disappear.png">'
	print '\t\t\t\t<grid pos="0,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<image file="piece'+str(i)+'/disappear.png">'
	print '\t\t\t\t<grid pos="50,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<image file="piece'+str(i)+'/disappear.png">'
	print '\t\t\t\t<grid pos="100,0" size="50,50" />'
	print '\t\t\t</image>'
	print ''
	print '\t\t\t<animation speed="50" />'
	print '\t\t</sprite>'
	print ''
	print '\t\t<!-- Little sprite, that you see in the next step or in the preview -->'
	print '\t\t<sprite name = "little">'
	print '\t\t\t<image file = "piece'+str(i)+'/little.png" />'
	print '\t\t</sprite>'
	print ''
	if(i>3):
		print '\t\t<sprite name= "hidder">'
		print '\t\t\t<image file ="piece'+str(i)+'/hidder.png" />'
		print '\t\t</sprite>'
		print ''
	print '\t\t<!-- Coords of the sprite in the preview area -->'
	print '\t\t<integer name = "progress-x" value = "17" />'
	print '\t\t<integer name = "progress-y" value = "'+str(60+(i-1)*45)+'" />'
	print ''
	print '\t</section>'
	print ''
	print ''

	
	
