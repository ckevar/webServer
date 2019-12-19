let img;

function setup() {
  createCanvas(720, 400);
  img = loadImage('CAReProducts.png');
}

function draw() {
	image(img, 0, height / 2, img.width / 2, img.height /2);
	console.log("lol")
}