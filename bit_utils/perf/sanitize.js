const proc = require('process');

let data = "";

proc.stdin.on('readable', ()=>{
	let chunk;
	while((chunk = proc.stdin.read()) != null){
		data += chunk;
	}	
});

proc.stdin.on('end', ()=>{
	let json = JSON.parse(data);
	json = {benchmarks: json.benchmarks};
	proc.stdout.write(JSON.stringify(json));
});
