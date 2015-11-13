//
//  main.js
//
//  A project template for using arbor.js
//

//(function($){

  var Renderer = function(canvas){
    var canvas = $(canvas).get(0)
    var ctx = canvas.getContext("2d");
    var particleSystem
    var gfx = arbor.Graphics(canvas)
    var sys = null



    var that = {
      init:function(system){
        //
        // the particle system will call the init function once, right before the
        // first frame is to be drawn. it's a good place to set up the canvas and
        // to pass the canvas size to the particle system
        //
        // save a reference to the particle system for use in the .redraw() loop
        particleSystem = system

        // inform the system of the screen dimensions so it can map coords for us.
        // if the canvas is ever resized, screenSize should be called again with
        // the new dimensions
        particleSystem.screenSize(canvas.width, canvas.height) 
        particleSystem.screenPadding(80) // leave an extra 80px of whitespace per side
        
        // set up some event handlers to allow for node-dragging
        that.initMouseHandling()
      },
      
      redraw:function(){
        // 
        // redraw will be called repeatedly during the run whenever the node positions
        // change. the new positions for the nodes can be accessed by looking at the
        // .p attribute of a given node. however the p.x & p.y values are in the coordinates
        // of the particle system rather than the screen. you can either map them to
        // the screen yourself, or use the convenience iterators .eachNode (and .eachEdge)
        // which allow you to step through the actual node objects but also pass an
        // x,y point in the screen's coordinate system
        // 
        ctx.fillStyle = "white"
        ctx.fillRect(0,0, canvas.width, canvas.height)
       

        //dessine les liens
	particleSystem.eachEdge(function(edge, pt1, pt2){
	if (edge.source.data.alpha * edge.target.data.alpha == 0) return
	gfx.line(pt1, pt2, {stroke:"#151B8D", width:(edge.data.weight/2), alpha:edge.target.data.alpha})
	})


        // on dessine les noeuds
	particleSystem.eachNode(function(node, pt){
        
		var w = Math.max(20, 20+gfx.textWidth(node.name) )
		if (node.data.alpha===0) return
					     if (node.data.shape=='dot'){
						 gfx.oval(pt.x-w/2, pt.y-w/2, w, w, {fill:node.data.color, alpha:node.data.alpha})
						 gfx.text(node.name, pt.x, pt.y+7, {color:"white", align:"center", font:"Arial", size:12})
						 gfx.text(node.name, pt.x, pt.y+7, {color:"white", align:"center", font:"Arial", size:12})
					     }else{
						 gfx.rect(pt.x-w/2, pt.y-8, w, 20, 4, {fill:node.data.color, alpha:node.data.alpha})
						 gfx.text(node.name, pt.x, pt.y+9, {color:"white", align:"center", font:"Arial", size:12})
						 gfx.text(node.name, pt.x, pt.y+9, {color:"white", align:"center", font:"Arial", size:12})
					     }

	    })



  

	},
      
      initMouseHandling:function(){
        // no-nonsense drag and drop (thanks springy.js)
        var dragged = null;

        // set up a handler object that will initially listen for mousedowns then
        // for moves and mouseups while dragging
        var handler = {
          clicked:function(e){
            var pos = $(canvas).offset();
            _mouseP = arbor.Point(e.pageX-pos.left, e.pageY-pos.top)
            dragged = particleSystem.nearest(_mouseP);

            if (dragged && dragged.node !== null){
              // while we're dragging, don't let physics move the node
              dragged.node.fixed = true
            }

            $(canvas).bind('mousemove', handler.dragged)
            $(window).bind('mouseup', handler.dropped)

            return false
          },
          dragged:function(e){
            var pos = $(canvas).offset();
            var s = arbor.Point(e.pageX-pos.left, e.pageY-pos.top)

            if (dragged && dragged.node !== null){
              var p = particleSystem.fromScreen(s)
              dragged.node.p = p
            }

            return false
          },

          dropped:function(e){
            if (dragged===null || dragged.node===undefined) return
            if (dragged.node !== null) dragged.node.fixed = false
            dragged.node.tempMass = 1000
            dragged = null
            $(canvas).unbind('mousemove', handler.dragged)
            $(window).unbind('mouseup', handler.dropped)
            _mouseP = null
            return false
          }
        }
        
        // start listening
        $(canvas).mousedown(handler.clicked);

	},
      
    }
    return that
  };


var gsensors = function(){};
    

     gsensors.init = function () { 

	 this.sys = arbor.ParticleSystem(500, 600, 0.5) // create the system with sensible repulsion/stiffness/friction                                
	 this.sys.parameters({gravity:true}) // use center-gravity to make the graph settle nicely (ymmv)                                                            
	 this.sys.renderer = Renderer("#viewport") // our newly created renderer will have its .init() method called shortly by sys...        

	 //	 this.data = $.getJSON("test.json",function(data){
	 //	 gsensors.sys.graft({nodes:data.nodes, edges:data.edges})
	 //    })
};
  

   gsensors.update = function(){ 

       //         var data = $.getJSON("test2.json",function(data){
       //        this.sys.graft({nodes:data.nodes, edges:data.edges})
       //	   })

       $.ajaxSetup({cache:false});
           this.data = $.getJSON("test2.json",function(data){ gsensors.sys.graft({nodes:data.nodes, edges:data.edges}) })
       //       this.data = $.getJSON('test.json'+ new Date().getTime(),function(data){ gsensors.sys.graft({nodes:data.nodes, edges:data.edges}) })

       //       this.data = $.ajax({cache: false,success: function(data) {gsensors.sys.graft({nodes:data.nodes, edges:data.edges}) }, url: 'test.json'});



       //   alert("Hello")

       setTimeout('gsensors.update();', 500);


};


  $(document).ready(function(){
	  //var sys = arbor.ParticleSystem(500, 600, 0.5) // create the system with sensible repulsion/stiffness/friction
	  //    sys.parameters({gravity:true}) // use center-gravity to make the graph settle nicely (ymmv)
	  //    sys.renderer = Renderer("#viewport") // our newly created renderer will have its .init() method called shortly by sys...
	
		gsensors.init();
		gsensors.update();

		//	var data = $.getJSON("test.json",function(data){
		//	sys.graft({nodes:data.nodes, edges:data.edges})
		//})
    
});

      //})(this.jQuery)