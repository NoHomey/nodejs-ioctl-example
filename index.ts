/// <reference path="typings/index.d.ts" />

import { ioctl, Ioctl } from 'ioctl-ulong';
import { IOCTL_EXAMPLE } from './IOCTL_EXAMPLE';
import { openIoctlSync } from 'open-ioctl';
import { closeSync } from 'fs';
import { O_NONBLOCK } from 'constants';

function printIoctl(res: Ioctl) {
    console.log(`Ioctl: .ioctl = ${res.ioctl} .data = ${res.data}`);
}

// floating: float to be converted to unsigned long
function fromFloat(floating: number): number {
    let num: string[] = floating.toString().split('.'); // Forming [a, b]
    let n: number = Number(num[0]) << 16; // n = a{16 bits}0{16 bits}
    return n | Number(num[1]); // return a{16 bits}b{16 bits}
}

// ulong: unsigned long
function fromUlong(ulong: number): number {
    let integral: number = ulong >> 16; // integral = 16 Most significant bits from ulong
    let fraction: number = ulong & 65535; // integral = 16 Least significant bits from ulong
    return parseFloat(integral + '.' + fraction); // return Float(integral.fraction)
}

function checkForAddition(fd: number) {
    let additon: Ioctl = ioctl(fd, IOCTL_EXAMPLE.IOCTL_EXAMPLE_ADDITION); // _IO
    // .ioctl will be what ioctl returned if it was a non negative integer (value by value)
    // .data will be 0

    printIoctl(additon);
    console.log(`Addition: ${Boolean(additon.ioctl)}`); // Addition true | false
}

let result: Ioctl;
let fd: number = openIoctlSync('ioctl_example_dev'); // Open device driver in (3) ioctl non-blocking model;

result = ioctl(fd, IOCTL_EXAMPLE.IOCTL_EXAMPLE_SET, fromFloat(12.3451)); // _IOR
// .ioctl will be what ioctl returned if it was a non negative integer
// .data will be what was passed to ioctl

printIoctl(result);
console.log(`Setting: ${fromUlong(result.data)}`); // Setting: 12.3451

result = ioctl(fd, IOCTL_EXAMPLE.IOCTL_EXAMPLE_GET); // _IOW
// .ioctl will be what ioctl returned if it was a non negative integer
// .data will be what was passed from the kernel (device driver) (value by reference)

printIoctl(result);
console.log(`Getting: ${fromUlong(result.data)}`); // Getting: 12.3451

checkForAddition(fd); // Addition: false

result = ioctl(fd, IOCTL_EXAMPLE.IOCTL_EXAMPLE_ADD, fromFloat(23.5786)); // _IOWR
// .ioctl will be what ioctl returned if it was a non negative integer
// .data will be what was passed from the kernel (device driver) (value by reference)

printIoctl(result);
console.log(`Result: ${fromUlong(result.data)}`); // Result: 35.9237

checkForAddition(fd); // Addition: true

closeSync(fd); // Release device driver*/