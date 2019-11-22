let ctx = document.getElementById("canvas1").getContext('2d');

let bm_data = fetch('https://raw.githubusercontent.com/adebreceni/Glass/master/bit_utils/perf/result.json').then(res=>{
	return res.text().then(str=>JSON.parse(str));
})

const group_idx = 1;

const colors = [
	{backgroundColor: "rgba(56, 200, 56, .5)", hoverBackgroundColor: "rgba(56, 200, 56, 1)"},
	{backgroundColor: "rgba(56, 56, 200, .5)", hoverBackgroundColor: "rgba(56, 56, 200, 1)"}
]

async function Init(){
	let data = await bm_data;
	data.benchmarks.forEach(bm=>bm.name = bm.name.split('/'));
	let group_names = [...new Set(data.benchmarks.map(bm=>bm.name[group_idx]))];
	let groups = group_names.map(group=>data.benchmarks.filter(bm=>bm.name[group_idx] === group));
	let chart = new Chart(ctx, {
		type: "bar",
		options:{
			scales:{
				yAxes: [{
					scaleLabel: {
						display: true,
						labelString: groups[0][0].time_unit
					}
				}]
			}
		},
		data: {
			labels: groups[0].map(bm=>bm.name.slice(2).join("/")),
			datasets: groups.map((group, idx)=>({data: group.map(bm=>bm.cpu_time), label: `v${idx + 1}`,...colors[idx % colors.length]}))
		}
	})
}

Init();