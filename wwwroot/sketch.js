let img;

function setup() {
  img = loadImage('CAReProducts.png');
  console.log(img.width)
  createCanvas(884, 417);
}

function draw() {
	// console.log(img.height)
	image(img, 0, 0, img.width / 2, img.height /2);
	// image(img, 0, 0);
	console.log("lol")
}